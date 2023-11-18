#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// https://leetcode.com/problems/merge-k-sorted-lists

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *mergeKLists(std::vector<ListNode *> &lists)
{
  struct Compare {
    constexpr bool operator () (const ListNode *a, const ListNode *b)
    { return a->val >= b->val; }
  };

  std::priority_queue<ListNode *, std::vector<ListNode *>, Compare> queue;

  for (const auto l : lists) {
    if (l != nullptr) {
      queue.push (l);
    }
  }

  if (queue.size () == 0) {
    return nullptr;
  }

  ListNode *r, *a;
  r = queue.top ();
  a = r;
  queue.pop ();
  ListNode *top;
  while (!queue.empty ()) {
    top = queue.top ();
    for (;;) {
      if (a->next == nullptr) {
        a->next = top;
        a = top;
        break;
      } else if (a->next->val <= top->val) {
        a = a->next;
      } else {
        queue.push (a->next);
        a->next = top;
        break;
      }
    }
    queue.pop ();
  }

  return r;
}

ListNode *vecToListNode (const std::vector<int> &v)
{
  ListNode *r, *a;

  if (v.size () == 0) {
    return nullptr;
  }

  auto it = v.begin ();
  r = new ListNode;
  r->val = *it;
  a = r;
  while (++it != v.end ()) {
    a->next = new ListNode;
    a = a->next;
    a->val = *it;
  }
  a->next = nullptr;

  return r;
}

std::vector<int> listNodeToVec (ListNode *l)
{
  std::vector<int> v;

  while (l) {
    v.push_back (l->val);
    l = l->next;
  }

  return v;
}


void printListNodes (ListNode *l)
{
  while (l) {
    std::cout << " " << l->val << std::endl;
    l = l->next;
  }
}

ListNode *simpleMergeKLists (std::vector<ListNode *> &lists)
{
  // simply convert lists to vectors, append those, then sort the
  // result vector
  std::vector<int> v;

  for (const auto &l : lists) {
    std::vector<int> v2 = listNodeToVec (l);
    v.insert (v.end (), v2.begin (), v2.end ());
  }

  std::sort (v.begin (), v.end ());

  ListNode *lSorted = vecToListNode (v);

  return lSorted;
}

void deleteListNodes (ListNode *l)
{
  ListNode *lNext;

  while (l != nullptr) {
    lNext = l->next;
    delete l;
    l = lNext;
  }
}

int main ()
{
  std::vector<int> v1 = {1, 4, 5, 7};
  std::vector<int> v2 = {3, 5, 6, 6};
  std::vector<int> v3 = {-1, 0, 1, 10};
  std::vector<int> v4 = {};
  std::vector<int> v5 = {0};
  std::vector<int> v6 = {-10, -4, 20, 25, 27};

  std::vector<ListNode *> v = {vecToListNode (v1), vecToListNode (v2),
                               vecToListNode (v3), vecToListNode (v4),
                               vecToListNode (v5), vecToListNode (v6)};

  // ListNode *l1 = vecToListNode (v1);
  // printListNodes (l1);
  // delete (l1);

  // ListNode *lr = simpleMergeKLists (v);
  // printListNodes (lr);
  // delete (lr);

  ListNode *lr = mergeKLists (v);
  printListNodes (lr);
  delete (lr);

  return 0;
}
