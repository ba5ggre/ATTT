#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

void swap_int(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int N;
    cout << "Nhap N : ";
    cin >> N;
    cin.ignore();

    vector<int> S(N);

    // Chọn kiểu key
    cout << "Chon kieu key:\n1. Ky tu (ASCII)\n2. So (danh sach)\nLua chon: ";
    int choice;
    cin >> choice;
    cin.ignore();

    vector<int> K;

    