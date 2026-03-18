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

    if (choice == 1) {
        // Key dạng chuỗi
        char key[256];
        cout << "Nhap key: ";
        cin.getline(key, 256);

        int len = strlen(key);
        for (int i = 0; i < len; i++) {
            K.push_back((unsigned char)key[i]);
        }
    } else {
        // Key dạng số (vd: 2 4 1 7)
        cout << "Nhap so phan tu key: ";
        int len;
        cin >> len;

        cout << "Nhap key (cach nhau boi space): ";
        for (int i = 0; i < len; i++) {
            int x;
            cin >> x;
            K.push_back(x);
        }
    }

    cin.ignore();
    char plaintext[1024];
    cout << "Nhap plaintext: ";
    cin.getline(plaintext, 1024);

    int msglen = strlen(plaintext);
    int keylen = K.size();

    // Khởi tạo S
    for (int i = 0; i < N; i++) S[i] = i;

    // KSA
    int j = 0;
    for (int i = 0; i < N; i++) {
        j = (j + S[i] + K[i % keylen]) % N;
        swap_int(S[i], S[j]);
    }
cout << "\n--- KET QUA MA HOA ---\n";
    cout << "Ky tu goc | Ky tu ma | ASCII\n";
    cout << "--------------------------------\n";

    int i = 0;
    j = 0;

    for (int n = 0; n < msglen; n++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap_int(S[i], S[j]);

        int t = (S[i] + S[j]) % N;
        int k = S[t];

        unsigned char cipher = (unsigned char)plaintext[n] ^ k;

        cout << plaintext[n] << "          | "
             << (char)cipher << "         | "
             << (int)cipher << endl;
    }

    return 0;
}