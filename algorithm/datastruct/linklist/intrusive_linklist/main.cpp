#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

using uint32 = std::uint32_t;

// ============================
// TC: LinkedListElement / Head
// ============================
class LinkedListHead;

// 侵入式链表，即对象本身也作为链表节点
class LinkedListElement {
private:
  friend class LinkedListHead;

  LinkedListElement *iNext;
  LinkedListElement *iPrev;

public:
  LinkedListElement() : iNext(nullptr), iPrev(nullptr) {}
  ~LinkedListElement() { delink(); }

  bool hasNext() const { return (iNext && iNext->iNext != nullptr); }
  bool hasPrev() const { return (iPrev && iPrev->iPrev != nullptr); }
  bool isInList() const { return (iNext != nullptr && iPrev != nullptr); }

  LinkedListElement *next() { return hasNext() ? iNext : nullptr; }
  LinkedListElement const *next() const { return hasNext() ? iNext : nullptr; }
  LinkedListElement *prev() { return hasPrev() ? iPrev : nullptr; }
  LinkedListElement const *prev() const { return hasPrev() ? iPrev : nullptr; }

  LinkedListElement *nocheck_next() { return iNext; }
  LinkedListElement const *nocheck_next() const { return iNext; }
  LinkedListElement *nocheck_prev() { return iPrev; }
  LinkedListElement const *nocheck_prev() const { return iPrev; }

  void delink() {
    if (!isInList())
      return;

    iNext->iPrev = iPrev;
    iPrev->iNext = iNext;
    iNext = nullptr;
    iPrev = nullptr;
  }

  // 插到 this 之前
  void insertBefore(LinkedListElement *pElem) {
    pElem->iNext = this;
    pElem->iPrev = iPrev;
    iPrev->iNext = pElem;
    iPrev = pElem;
  }

  // 插到 this 之后
  void insertAfter(LinkedListElement *pElem) {
    pElem->iPrev = this;
    pElem->iNext = iNext;
    iNext->iPrev = pElem;
    iNext = pElem;
  }

private:
  LinkedListElement(LinkedListElement const &) = delete;
  LinkedListElement &operator=(LinkedListElement const &) = delete;
};

class LinkedListHead {
private:
  LinkedListElement iFirst;
  LinkedListElement iLast;
  uint32 iSize;

public:
  LinkedListHead() : iSize(0) {
    iFirst.iNext = &iLast;
    iLast.iPrev = &iFirst;
  }
  ~LinkedListHead() {}

  bool isEmpty() const { return (!iFirst.iNext->isInList()); }

  LinkedListElement *getFirst() { return (isEmpty() ? nullptr : iFirst.iNext); }
  LinkedListElement const *getFirst() const {
    return (isEmpty() ? nullptr : iFirst.iNext);
  }

  LinkedListElement *getLast() { return (isEmpty() ? nullptr : iLast.iPrev); }
  LinkedListElement const *getLast() const {
    return (isEmpty() ? nullptr : iLast.iPrev);
  }

  void insertFirst(LinkedListElement *pElem) { iFirst.insertAfter(pElem); }
  void insertLast(LinkedListElement *pElem) { iLast.insertBefore(pElem); }

  uint32 getSize() const {
    if (!iSize) {
      uint32 result = 0;
      LinkedListElement const *e = getFirst();
      while (e) {
        ++result;
        e = e->next();
      }
      return result;
    }
    return iSize;
  }

  void incSize() { ++iSize; }
  void decSize() { --iSize; }

private:
  LinkedListHead(LinkedListHead const &) = delete;
  LinkedListHead &operator=(LinkedListHead const &) = delete;
};

// ============================
// TC: Reference
// ============================
template <class TO, class FROM>
class Reference : public LinkedListElement {
private:
  TO *iRefTo;
  FROM *iRefFrom;

protected:
  virtual void targetObjectBuildLink() = 0;
  virtual void targetObjectDestroyLink() = 0;
  virtual void sourceObjectDestroyLink() = 0;

public:
  Reference() : iRefTo(nullptr), iRefFrom(nullptr) {}
  virtual ~Reference() {}

  void link(TO *toObj, FROM *fromObj) {
    assert(fromObj);
    if (isValid())
      unlink();

    if (toObj != nullptr) {
      iRefTo = toObj;
      iRefFrom = fromObj;
      targetObjectBuildLink();
    }
  }

  void unlink() {
    // source 主动断链
    targetObjectDestroyLink();
    delink();
    iRefTo = nullptr;
    iRefFrom = nullptr;
  }

  void invalidate() {
    // target 被销毁导致失效：iRefFrom 保留，iRefTo 置空
    sourceObjectDestroyLink();
    delink();
    iRefTo = nullptr;
  }

  bool isValid() const { return iRefTo != nullptr; }

  TO *getTarget() const { return iRefTo; }
  FROM *GetSource() const { return iRefFrom; }

private:
  Reference(Reference const &) = delete;
  Reference &operator=(Reference const &) = delete;
};

// ============================
// Example domain: Player <-> Creature
// ============================
class Player; // FROM

class Creature // TO
{
public:
  explicit Creature(uint32 id_) : id(id_) {}

  uint32 id;
  LinkedListHead refs; // 反向索引：所有引用我的 Reference 节点都挂在这里

  ~Creature() {
    // 关键：target 销毁时，遍历所有引用者并 invalidate
    LinkedListElement *node = refs.getFirst();
    while (node) {
      LinkedListElement *next =
          node->next(); // invalidate 会 delink，必须先存 next
      auto *ref = static_cast<Reference<Creature, Player> *>(node);
      ref->invalidate();
      refs.decSize();
      node = next;
    }

    std::cout << "[Creature#" << id << "] destroyed, invalidated all refs\n";
  }
};

class Player // FROM
{
public:
  explicit Player(std::string name_) : name(std::move(name_)) {}

  std::string name;

  class TargetRef : public Reference<Creature, Player> {
  protected:
    void targetObjectBuildLink() override {
      // 将“本 Reference 节点(this)”挂到 target(Creature) 的 refs 链表尾部
      getTarget()->refs.insertLast(this);
      getTarget()->refs.incSize();

      std::cout << "  [link] " << GetSource()->name << " -> Creature#"
                << getTarget()->id
                << " (creature.refs=" << getTarget()->refs.getSize() << ")\n";
    }

    void targetObjectDestroyLink() override {
      // source 主动断开：从 target 的 refs 链表摘掉自己
      if (getTarget() && this->isInList()) {
        this->delink();
        getTarget()->refs.decSize();

        std::cout << "  [unlink] " << GetSource()->name
                  << " removed from Creature#" << getTarget()->id
                  << " (creature.refs=" << getTarget()->refs.getSize() << ")\n";
      }
    }

    void sourceObjectDestroyLink() override {
      // target 销毁：通知 source 做清理
      std::cout << "  [invalidate] " << GetSource()->name
                << " target became null (creature destroyed)\n";
    }
  };

  TargetRef target;

  void SelectTarget(Creature *c) {
    target.link(c, this);
  }
  void ClearTarget() {
    if (target.isValid())
      target.unlink();
  }
  bool HasTarget() const {
    return target.isValid();
  }
};

// ============================
// Demo
// ============================
int main() {
  Player alice("Alice");
  Player bob("Bob");
  Player cathy("Cathy");

  Creature *wolf = new Creature(1001);

  std::cout << "== Multiple sources link to same target ==\n";
  alice.SelectTarget(wolf);
  bob.SelectTarget(wolf);
  cathy.SelectTarget(wolf);

  std::cout << "Creature.refs size: " << wolf->refs.getSize() << "\n\n";

  std::cout << "== One source unlinks (Bob) ==\n";
  bob.ClearTarget();
  std::cout << "Creature.refs size: " << wolf->refs.getSize() << "\n";
  std::cout << "Alice has target? " << alice.HasTarget() << "\n";
  std::cout << "Bob   has target? " << bob.HasTarget() << "\n";
  std::cout << "Cathy has target? " << cathy.HasTarget() << "\n\n";

  std::cout << "== Target destroyed -> invalidates remaining refs ==\n";
  delete wolf;

  std::cout << "\n== After target deletion ==\n";
  std::cout << "Alice has target? " << alice.HasTarget() << "\n";
  std::cout << "Bob   has target? " << bob.HasTarget() << "\n";
  std::cout << "Cathy has target? " << cathy.HasTarget() << "\n";

  return 0;
}
