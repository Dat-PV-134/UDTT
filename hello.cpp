#include <bits/stdc++.h>

using namespace std;

typedef struct Quat {
	std::string tenHang;
	std::string mauSac;
	int giaBan;

	void xuat() {
		std::cout << tenHang << std::setw(20) << mauSac << std::setw(20) << giaBan << std::endl;
	}
} QType;

void hienThiDS(QType a[], int n) {
	std::cout << "DANH SACH QUAT" << std::endl;
	for (int i = 0; i < n; i++) {
		a[i].xuat();
	}
}

int muaQuat(QType a[], int n, int p, QType res[]) {
	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(p + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= p; j++) {
			if (a[i - 1].giaBan <= j) {
				dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - a[i - 1].giaBan] + a[i - 1].giaBan);
			} else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	int dem = 0;
	int i = n;
	int j = p;
	while (i > 0 && j > 0) {
		if (dp[i][j] != dp[i - 1][j]) {
			res[dem++] = a[i - 1];
			j -= a[i - 1].giaBan;
		}
		i--;
	}

	return dem;
}

void quickSort(QType a[], int left, int right) {
	if (left < right) {
		int k = (left + right) / 2;
		QType t = a[k];
		int i = left, j = right;
		do {
			while (a[i].giaBan < t.giaBan) i++;
			while (a[j].giaBan > t.giaBan) j--;
			if (i <= j) {
				QType tg = a[i];
				a[i] = a[j];
				a[j] = tg;
				i++;
				j--;
			}
		} while (i <= j);
		quickSort(a, left, j);
		quickSort(a, i, right);
	}
}

int greedyRes(QType a[], int n, int p, QType res[]) {
	int cnt = 0;
	int i = n - 1;
	while (p > 0 && i > 0) {
		res[cnt] = a[i];
		p -= a[i].giaBan;
		cnt++;
		i--;
	}
	return cnt;
}

int main() {
	QType a[100];
	int n = 6;
	long p = 700000;
	QType res[100];
	a[0] = {"Quat 1", "Do", 400000};
	a[1] = {"Quat 2", "Vang", 800000};
	a[2] = {"Quat 3", "Cam", 500000};
	a[3] = {"Quat 4", "Luc", 300000};
	a[4] = {"Quat 5", "Lam", 900000};
	a[5] = {"Quat 6", "Tim", 700000};
	
	hienThiDS(a, n);

	int dem = muaQuat(a, n, p, res);
	std::cout << "Can ban it nhat " << dem << " chiec quat ban." << std::endl;
	std::cout << std::endl << "DANH SACH QUAT BAN DUOC: " << std::endl;
	if (dem != 0) {
		for (int i = dem - 1; i >= 0; i--) {
			std::cout << res[i].tenHang << std::setw(20) << res[i].giaBan << std::endl;
		}
	}

	quickSort(a, 0, n - 1);
	hienThiDS(a, n);

	int dem2 = greedyRes(a, n, p, res);
	std::cout << "Can ban it nhat " << dem2 << " chiec quat ban." << std::endl;
	std::cout << std::endl << "DANH SACH QUAT BAN DUOC: " << std::endl;
	if (dem != 0) {
		for (int i = dem2 - 1; i >= 0; i--) {
			std::cout << res[i].tenHang << std::setw(20) << res[i].giaBan << std::endl;
		}
	} 

	return 0;
}
