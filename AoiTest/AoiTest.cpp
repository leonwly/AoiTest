// AoiTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <string>

using namespace std;

// 双链表(对象)
class DoubleNode
{
public:
	DoubleNode(string key, int x, int y)
	{
		this->key = key;
		this->x = x;
		this->y = y;
		xPrev = xNext = NULL;
	}

	DoubleNode* xPrev;
	DoubleNode* xNext;
	DoubleNode* yPrev;
	DoubleNode* yNext;

	string key;
	int x;
	int y;

private:

};

//地图场景
class Scene
{
public:
	Scene()
	{
		this->_head = new DoubleNode("[head]", 0, 0);
		this->_tail = new DoubleNode("[tail]", 0, 0);
		_head->xNext = _tail;
		_head->yNext = _tail;
		_tail->xPrev = _head;
		_tail->yPrev = _head;
	}

	DoubleNode* Add(string name, int x, int y)
	{
		DoubleNode* node = new DoubleNode(name, x, y);
		_add(node);
		return node;
	}

	void Leave(DoubleNode* node)
	{
		node->xPrev->xNext = node->xNext;
		node->xNext->xPrev = node->xPrev;
		node->yPrev->yNext = node->yNext;
		node->yNext->yPrev = node->yPrev;

		node->xPrev = NULL;
		node->xNext = NULL;
		node->yPrev = NULL;
		node->yNext = NULL;
	}

	void Move(DoubleNode* node, int x, int y)
	{
		Leave(node);
		node->x = x;
		node->y = y;
		_add(node);
	}

	//获取范围内的AOI(参数为查找范围)
	void PrintAOI(DoubleNode* node, int xAreaLen, int yAreaLen)
	{
		cout << "Cur is: " << node->key << "(" << node->x << "," << node->y << ")" << endl;
		cout << "Print AOI: " << endl;

		DoubleNode* cur = node->xNext;
		while (cur != _tail)
		{
			if ((cur->x - node->x) > xAreaLen)
			{
				break;
			}
			else
			{
				int inteval = 0;
				inteval = node->y - cur->y;
				if (inteval >= -yAreaLen && inteval <= yAreaLen)
				{
					cout << "\t" << cur->key << "(" << cur->x << "," << cur->y << ")" << endl;
				}
			}
			cur = cur->xNext;
		}

		cur = node->xPrev;
		while (cur != _head)
		{
			if ((node->x - cur->x) > xAreaLen)
			{
				break;
			}
			else
			{
				int inteval = 0;
				inteval = node->y - cur->y;
				if (inteval >= -yAreaLen && inteval <= yAreaLen)
				{
					cout << "\t" << cur->key << "(" << cur->x << "," << cur->y << ")" << endl;
				}
			}
			cur = cur->xPrev;
		}
	}

	//调试代码
	void PrintLink()
	{
		DoubleNode* cur = _head->xNext;
		while (cur != _tail)
		{
			cout << (cur->key) << "(" << (cur->x) << "," << (cur->y) << ") -> ";
			cur = cur->xNext;
		}
		cout << "end" << endl;

		cur = _head->yNext;
		while (cur != _tail)
		{
			cout << (cur->key) << "(" << (cur->x) << "," << (cur->y) << ") -> ";
			cur = cur->yNext;
		}
		cout << "end" << endl;
	}

private:
	DoubleNode* _head;
	DoubleNode* _tail;

	void _add(DoubleNode* node)
	{
		DoubleNode* cur = _head->xNext;
		while (cur != NULL)
		{
			if ((cur->x > node->x) || cur == _tail)
			{
				node->xNext = cur;
				node->xPrev = cur->xPrev;
				cur->xPrev->xNext = node;
				cur->xPrev = node;
				break;
			}
			cur = cur->xNext;
		}

		cur = _head->yNext;
		while (NULL != cur)
		{
			if ((cur->y > node->y) || cur == _tail)
			{
				node->yNext = cur;
				node->yPrev = cur->yPrev;
				cur->yPrev->yNext = node;
				cur->yPrev = node;
				break;
			}
			cur = cur->yNext;
		}
	}
};


int main()
{
	Scene scene = Scene();
	scene.Add("a", 1, 5);
	scene.Add("f", 6, 6);
	scene.Add("c", 3, 1);
	scene.Add("b", 2, 2);
	scene.Add("e", 5, 3);
	DoubleNode* node = scene.Add("d", 3, 3);

	scene.PrintLink();
	scene.PrintAOI(node, 2, 2);

	cout << endl << "[MOVE]" << endl;
	scene.Move(node, 4, 4);
	scene.PrintLink();
	scene.PrintAOI(node, 2, 2);

	cout << endl << "[LEAVE]" << endl;
	scene.Leave(node);
	scene.PrintLink();

    return 0;
}

