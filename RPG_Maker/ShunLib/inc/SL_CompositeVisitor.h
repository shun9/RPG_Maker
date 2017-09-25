#pragma once

class INode;

class Visitor {
public:
	virtual void Visit(INode* pNode) = 0;
};

class INode
{
public:
	INode() {}
	virtual ~INode() {}

	// 子ノードを追加する
	virtual void AddChild(INode* node) = 0;

	// ビジターを迎え入れる
	virtual void Accept(Visitor* visitor) = 0;
};
