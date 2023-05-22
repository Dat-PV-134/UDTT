#include <bits/stdc++.h>

using namespace std;

class CV {
private:
	int maCV;
	int startTime;
	int endTime;

public:
	CV(){}
	CV(int maCV, int startTime, int endTime) {
		this->maCV = maCV;
		this->startTime = startTime;
		this->endTime = endTime;
	}

	int getWorkingTime() const {
		return endTime - startTime;
	}

	string toString() {
		return to_string(maCV) + " - " + to_string(startTime) + " - " + to_string(endTime);
	}

	int getMa() const {
		return maCV;
	}

	int getStart() const {
		return startTime;
	}

	int getEnd() const {
		return endTime;
	}

	bool operator<(CV other) {
		return this->endTime < other.endTime;
	}
};

/*
CV cvList[7] = {
    {0, 4, 9},
    {1, 13, 21},
    {2, 7, 9},
    {3, 5, 8},
    {4, 8, 13},
    {5, 9, 16},
    {6, 17, 22}
};
*/

CV cvList[7];
vector<CV> ans;
int count = 0;

void initList() {
	cvList[0] = CV(0, 4, 9);
	cvList[1] = CV(1, 13, 21);
	cvList[2] = CV(2, 7, 9);
	cvList[3] = CV(3, 5, 8);
	cvList[4] = CV(4, 8, 13);
	cvList[5] = CV(5, 9, 16);
	cvList[6] = CV(6, 17, 22);
}


int getTotalWorkingTime(CV cvList[], int n) {
	if (n == 1) return cvList[0].getWorkingTime();
	return cvList[n - 1].getWorkingTime() + getTotalWorkingTime(cvList, n - 1);
}

int cau2aCach1(CV cvList[], int n, vector<CV> &ans) {
	for (int i = 0; i < n; i++) {
		bool check = true;
		for (int j = 0; j < ans.size(); j++) {
			if (cvList[i].getEnd() > ans[j].getStart() && cvList[i].getStart() < ans[j].getEnd()) {
				check = false;
				break;
			}
		}
		if (check) ans.push_back(cvList[i]);
	}
	return ans.size();
}

void next_config(int x[], int k, int i) {
	 x[i] += 1;
	 i++;
	 while (i <= k) {
		 x[i] = x[i - 1] + 1;
		 i++;
	 }
}

void view_config(int x[], int k) {
	for (int i = 1; i <= k; i++) {
		cout << cvList[x[i] - 1].toString() << endl;
	}
	cout << endl;
}

void listing_config(int k, int n) {
	int i, x[k + 1] = {0};
	int count = 0;
	for (int i = 0; i <= k; i++) {
		x[i] = i;
	}
	do {
		count++;	
		view_config(x, k);
		i = k;
		while(i > 0 && x[i] == n - k + i) {
			i--;
		}
		if (i > 0) {
			next_config(x, k, i);
		}
	} while (i > 0);
	cout << count << endl;
}

void view_hoanvi(int x[], int n) {
	for (int i = 1; i <= n; i++) {
		cout << cvList[x[i]-1].toString() << endl;
	}
	cout << endl;
}

void next_hoanvi(int x[], int n, int i) {
	int k = n;
	while (x[k] < x[i]) {
		k--;
	}
	swap(x[i], x[k]);
	int j = n;
	i++;
	while (i < j) {
		swap(x[i], x[j]);
		i++;
		j--;
	}
}

void listing_hoanvi(int n) {
	int i, x[n + 1] = {0};
	int count = 0;
	for (int i = 1; i <= n; i++) {
		x[i] = i;
	}
	do {
		count++;
		view_hoanvi(x, n);
		i = n - 1;
		while (i > 0 && x[i] > x[i + 1]) i--;
		if (i > 0) {
			next_hoanvi(x, n, i);
		}
	} while (i > 0);
	cout << endl << count << endl;
}

string convertFloatToString(float number, int n) {
	string res = "";
	
	string strNguyen = "";
	int tempNguyen = (int) number;
	int count = 0;
	while (tempNguyen > 0) {
		strNguyen += (tempNguyen % 10) + '0';
		tempNguyen /= 10;
		count++;
	}
	for (int i = count - 1; i >= 0; i--) {
		res += strNguyen[i];
	}

	res += ".";

	float thapPhan = number - (int) number;
	while (n > 0) {
		thapPhan *= 10;
		if (n == 1) thapPhan += 0.5f;
		res += ((int) (thapPhan)) + '0';
		thapPhan -= (int) thapPhan;
		n--;
	}

	return res;
}

int main() {
	initList();
	cout << getTotalWorkingTime(cvList, 7);
	sort(cvList, cvList + 6);
	cout << endl;
	for (int i = 0; i < 7; i++) {
		cout << cvList[i].toString() << endl;
	}
	cout << "----------------------------" << endl;
	int kq = cau2aCach1(cvList, 7, ans);
	cout << kq << endl;
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].toString() << endl;
	}
	cout << "---------------------------------" << endl;
	//listing_config(5, 7);
	cout << "---------------------------------" << endl;
	listing_hoanvi(7);
}

