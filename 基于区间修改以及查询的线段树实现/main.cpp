#include <iostream>
using namespace std;

class Node
{
public:
	int l, r, sum, lazy_tag;
	Node()
	{

	}
	Node(int l, int r)
	{
		this->l = l, this->r = r;
	}
};

class Segment_Tree
{
private:
	Node* ptr;
public:
	Segment_Tree(int num)
	{
		ptr = (Node*)malloc(sizeof(Node) * 6 * (num));
	}

	void push_up(Node& root, Node& left, Node& right)
	{
		root.sum = left.sum + right.sum;
	}

	void build(int id, int l, int r, int a[])
	{
		if (l >= r)
		{
			ptr[id].l = l, ptr[id].r = r, ptr[id].sum = a[l], ptr[id].lazy_tag = 0;
			return;
		}
		int mid = (l + r) >> 1;
		ptr[id].l = l, ptr[id].r = r, ptr[id].lazy_tag = 0;
		build(id << 1, l, mid, a), build(id << 1 | 1, mid + 1, r, a);
		push_up(ptr[id], ptr[id << 1], ptr[id << 1 | 1]);
	}

	void push_down(Node& root, Node& left, Node& right)
	{
		if (root.lazy_tag == 0) return;
		left.sum += (left.r - left.l + 1) * root.lazy_tag;
		right.sum += (right.r - right.l + 1) * root.lazy_tag;
		left.lazy_tag += root.lazy_tag;
		right.lazy_tag += root.lazy_tag;
		root.lazy_tag = 0;
	}

	void modify(int id, int l, int r, int ad)
	{
		push_down(ptr[id], ptr[id << 1], ptr[id << 1 | 1]);
		if (ptr[id].l >= l && ptr[id].r <= r)
		{
			ptr[id].lazy_tag += ad;
			ptr[id].sum += (ptr[id].r - ptr[id].l + 1) * ad;
			return;
		}
		int mid = (ptr[id].l + ptr[id].r) >> 1;
		if (l <= mid)  modify(id << 1, l, r, ad);
		if (r > mid)   modify(id << 1 | 1, l, r, ad);
		push_up(ptr[id], ptr[id << 1], ptr[id << 1 | 1]);
	}

	int query(int id, int l, int r)
	{
		if (ptr[id].l >= l && ptr[id].r <= r)
		{
			return ptr[id].sum;
		}
		push_down(ptr[id], ptr[id << 1], ptr[id << 1 | 1]);
		int mid = (ptr[id].l + ptr[id].r) >> 1;
		int sum = 0;
		if (l <= mid) sum += query(id << 1, l, r);
		if (r > mid)  sum += query(id << 1 | 1, l, r);
		push_up(ptr[id], ptr[id << 1], ptr[id << 1 | 1]);
		return sum;
	}

};


int main()
{
	int n, q;
	int* a;
	cin >> n >> q;
	Segment_Tree Tree(n + 10);
	a = (int*)malloc(sizeof(int) * (n));

	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	Tree.build(1, 1, n, a);

	while (q--)
	{
		int op, l, r, k;
		cin >> op;
		if (op == 1)
		{
			cin >> l >> r >> k;
			Tree.modify(1, l, r, k);
		}
		else
		{
			cin >> l >> r;
			cout << Tree.query(1, l, r) << "\n";
		}
	}


	return 0;

}