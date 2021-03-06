#include <stdio.h>
#include <iostream>
#include <stack>
#define FINAL_MAIN
#pragma warning(disable:4996)

using namespace std;

typedef struct {
	int opt;
	int final_right;
}solution;


#ifdef VER_1
int max_square(int* h, int end_at, int& final_right) {
	int temp = h[end_at + 1];
	h[end_at + 1] = -1;
	int left[11010], right[11010];
	left[0] = right[0] = 0;
	for (int i = 1; i <= end_at; i++) {
		left[i] = right[i] = i;
	}
	for (int i = 1; i <= end_at; i++) {
		while (h[left[i] - 1] >= h[i]) {
			left[i] = left[left[i] - 1];
		}
	}
	for (int i = end_at; i >= 1; i--) {
		while (h[right[i] + 1] >= h[i]) {
			right[i] = right[right[i] + 1];
		}
	}
	int rtn = 0;
	for (int i = 1; i <= end_at; i++) {
		int tmpopt = (right[i] - left[i] + 1)*h[i];
		if ( tmpopt > rtn) {
			rtn = tmpopt;
			final_right = right[i];
		}
	}
	h[end_at + 1] = temp;
	return rtn;
}
#endif

solution max_square(int* h, int length) {
	solution ans; ans.opt = 0, ans.final_right = 0;
	if (length == 0) return ans;
	int h_[11010];
	for (int i = 0; i < length; i++) {
		h_[i] = h[i];
	}
	h_[length] = 0;
	stack<int> st;
	for (int i = 0; i < length + 1; i++)
	{
		while (!st.empty() && h_[i] < h_[st.top()]) {
			auto val = st.top();
			st.pop();
			//ans.opt = max(ans.opt, h_[val]*(i-1-(st.empty()?-1:st.top())));
			auto curr_max = h_[val] * (i - 1 - (st.empty() ? -1 : st.top()));
			if (curr_max > ans.opt) {
				ans.opt = curr_max;
				ans.final_right = i - 1;
			}
		}
		st.push(i);
	}
	return ans;
}

#ifdef FINAL_MAIN
int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int* h = new int[n], *hr = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &h[i]);
		hr[n- 1 - i] = h[i];
	}
	int* h_opt = new int[n], *hr_opt = new int[n];
	int* h_final_right = new int[n], *hr_final_right = new int[n];
	for (int i = 0; i < n; i++) {
		solution s = max_square(h, i+1), sr = max_square(hr, i+1);
		h_opt[i] = s.opt, h_final_right[i] = s.final_right;
		hr_opt[i] = sr.opt; hr_final_right[i] = sr.final_right;
	}
	int opt_result = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (h_opt[i] + hr_opt[j] > opt_result && h_final_right[i] + hr_final_right[j]+2 <= n - k)
				opt_result = h_opt[i] + hr_opt[j];
		}
	}
	printf("%d", opt_result);
	return 0;
}
#else
int main() {
	int h[] = { 5,4,7,1,3,6 };
	solution s = max_square();
	cout << s.opt << " "  << s.final_right << endl;
}
#endif