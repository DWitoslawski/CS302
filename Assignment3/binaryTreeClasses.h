#ifndef BIN_TREE_CLASSES_H
#define BIN_TREE_CLASSES_H

class binTreeNode
{
public:
	virtual double getWeight() { return 0.0; }
	void setLeft(binTreeNode * r) { left = r; }
	void setRight(binTreeNode * r) { right = r; }
	binTreeNode* getLeft() { return left; }
	binTreeNode* getRight() { return right; }
	void setArmLength(int arm) { armLength = arm; }
	int getArmLength()  { return armLength; }
	
private:
	binTreeNode * left, * right;
	int armLength;
};

class goped : public binTreeNode
{
public:
	goped(double w, double e, double t) :
		wheelWeight(w), engineWeight(e), tankWeight(t)
		 { }
	
	double getWeight()
	{
		return 2 * wheelWeight + engineWeight + tankWeight;
	}
private:
	double wheelWeight;
	double engineWeight;
	double tankWeight;
};

class bike : public binTreeNode
{
public:
	bike(double w, double f) :
		wheelWeight(w), frameWeight(f) { }

	double getWeight() { return 2 * wheelWeight + frameWeight; }
private:
	double wheelWeight;
	double frameWeight;
};

class car : public binTreeNode
{
public:
	car(double w, double e, double t, double b) :
		wheelWeight(w), engineWeight(e), transmissionWeight(t),
		bodyWeight(b) { }

	double getWeight()
	{
		return 4 * wheelWeight + engineWeight
		+ transmissionWeight + bodyWeight;
	}
private:
	double wheelWeight;
	double engineWeight;
	double transmissionWeight;
	double bodyWeight;
};
#endif