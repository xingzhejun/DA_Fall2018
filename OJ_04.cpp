/*
This did not get AC for an unknown memory bug. Trying to figure it out if time permits (or I can)
*/
#include <stdio.h>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#pragma warning(disable:4996)

struct HuffmanNode
{
	int rank;
	long long weight;
	HuffmanNode *LeftChild;
	HuffmanNode *RightChild;
	std::string result;
	HuffmanNode() { rank = -1; weight = 0; LeftChild = NULL; RightChild = NULL; result = ""; }
	/*bool operator < (const HuffmanNode& HN) const { return this->weight < HN.weight; }
	bool operator == (const HuffmanNode& HN) const { return this->weight == HN.weight; }
	bool operator > (const HuffmanNode& HN) const { return this->weight > HN.weight; }
	bool operator <= (const HuffmanNode& HN) const { return this->weight <= HN.weight; }
	bool operator >= (const HuffmanNode& HN) const { return this->weight >= HN.weight; }*/
};

class WeightCmp {
public:
	bool operator() (const HuffmanNode* HN1, const HuffmanNode* HN2) const {
		return HN1->weight < HN2->weight;
	}
};

class RankCmp {
public:
	bool operator() (const HuffmanNode* HN1, const HuffmanNode* HN2) const {
		return HN1->rank < HN2->rank;
	}
};

HuffmanNode* HuffmanMerge(HuffmanNode* LChild, HuffmanNode* RChild) {
	HuffmanNode* NewParent = new (std::nothrow) HuffmanNode();
	NewParent->LeftChild = LChild;
	NewParent->RightChild = RChild;
	NewParent->rank = -1;
	NewParent->weight = LChild->weight + RChild->weight;
	return NewParent;
}

long long traverse(HuffmanNode*& root, std::set<HuffmanNode*, RankCmp>& rstMap) {
	root->result = "";
	long long rtn = 0;
	std::queue<HuffmanNode*> tmpQueue;
	tmpQueue.push(root);
	while (!tmpQueue.empty()) {
		HuffmanNode* queueFirst = tmpQueue.front();
		tmpQueue.pop();
		if (queueFirst->LeftChild == NULL && queueFirst->RightChild == NULL) {
			if (queueFirst->result == "") {
				queueFirst->result = "0";
				rstMap.insert(queueFirst);
				return queueFirst->weight;
			}
			rstMap.insert(queueFirst);
			rtn += queueFirst->result.length() * queueFirst->weight;
		}
		if (queueFirst->LeftChild != NULL) {
			queueFirst->LeftChild->result = queueFirst->result;
			queueFirst->LeftChild->result += "0";
			tmpQueue.push(queueFirst->LeftChild);
		}
		if (queueFirst->RightChild != NULL) {
			queueFirst->RightChild->result = queueFirst->result;
			queueFirst->RightChild->result += "1";
			tmpQueue.push(queueFirst->RightChild);
		}
	}
	return rtn;
}

int main() {
	int n; 
	long long total = 0;
	scanf("%d", &n);
	std::multiset<HuffmanNode*, WeightCmp> HForest;
	long long* words = new (std::nothrow) long long[n];
	HuffmanNode* insNode = new (std::nothrow) HuffmanNode[n];
	for (int i = 0; i < n; i++) {
		scanf("%lld", &words[i]);
		total += words[i];
		insNode[i].rank = i;
		insNode[i].weight = words[i];
		HForest.insert(insNode+i);
	}
	delete[] words;
	while (HForest.size()>1) {
		HuffmanNode* tmpLC = *HForest.begin();
		HForest.erase(HForest.begin());
		HuffmanNode* tmpRC = *HForest.begin();
		HForest.erase(HForest.begin());
		HuffmanNode* NewHNode = HuffmanMerge(tmpLC, tmpRC);
		HForest.insert(NewHNode);
	}
	HuffmanNode* FinalTree = *HForest.begin();
	std::set<HuffmanNode*, RankCmp> ResultSet;
	long long code_len = traverse(FinalTree, ResultSet);
	double avg = (double)code_len / (double)total;
	printf("%f", avg);
	std::set<HuffmanNode*, RankCmp>::iterator it = ResultSet.begin();
	for (; it != ResultSet.end(); it++) {
		printf("\n%s", (*it)->result.c_str());
	}
	return 0;
}
