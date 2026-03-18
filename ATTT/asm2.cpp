#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct BuocTinh {
    int chi_so, so_du, thuong, v, w;
};

int tim_bac_da_thuc(int n) {
    if (n == 0) return -1;
    int bac = 0;
    while (n >>= 1) bac++;
    return bac;
}

int phep_nhan_gf2(int a, int b) {
    int ket_qua = 0;
    for (; b > 0; b >>= 1, a <<= 1) {
        if (b & 1) ket_qua ^= a;
    }
    return ket_qua;
}

void phep_chia_gf2(int a, int b, int &q, int &r) {
    q = 0;
    int bac_a = tim_bac_da_thuc(a);
    int bac_b = tim_bac_da_thuc(b);
    while (bac_a >= bac_b && bac_a != -1) {
        int lech = bac_a - bac_b;
        q |= (1 << lech);
        a ^= (b << lech);
        bac_a = tim_bac_da_thuc(a);
    }
    r = a;
}

void thuc_thi_euclidean_mo_rong(int m_poly, int so_can_tim) {
    vector<BuocTinh> bang_du_lieu;
    int r0 = m_poly, r1 = so_can_tim;
    int v0 = 1, v1 = 0;
    int w0 = 0, w1 = 1;

    bang_du_lieu.push_back({-1, r0, 0, v0, w0});
    bang_du_lieu.push_back({0, r1, 0, v1, w1});

    int k = 1;
    while (r1 != 0) {
        int q, r_moi;
        phep_chia_gf2(r0, r1, q, r_moi);

        int v_moi = v0 ^ phep_nhan_gf2(q, v1);
        int w_moi = w0 ^ phep_nhan_gf2(q, w1);

        bang_du_lieu.push_back({k++, r_moi, q, v_moi, w_moi});

        r0 = r1; r1 = r_moi;
        v0 = v1; v1 = v_moi;
        w0 = w1; w1 = w_moi;
    }

    cout << left << setw(8) << "Buoc i" << "| " << setw(8) << "r_i" << "| " << setw(8) << "q_i" << "| " << setw(8) << "v_i" << "| " << setw(8) << "w_i" << endl;
    cout << string(50, '-') << endl;

    for (const auto& dong : bang_du_lieu) {
        cout << left << setw(8) << dong.chi_so << "| " << setw(8) << dong.so_du << "| ";
        if (dong.chi_so <= 0) cout << setw(8) << "-" << "| ";
        else cout << setw(8) << dong.thuong << "| ";
        cout << setw(8) << dong.v << "| " << setw(8) << dong.w << endl;
    }

    if (r0 == 1) 
        cout << "\n=> Nghich dao nhan la: " << w0 << endl;
    else 
        cout << "\n=> Khong ton tai nghich dao trong truong nay." << endl;
    cout << endl;
}

int main() {
    // m(x) = x^10 + x^3 + 1 => 10000001001 (nhi phan) => 1033 (thap phan)
    int m_da_thuc = 1033; 
    
    int test_a = 523;
    int test_b = 1015;

    cout << "TIM NGHICH DAO CUA a = " << test_a << " TRONG GF(2^10)" << endl;
    thuc_thi_euclidean_mo_rong(m_da_thuc, test_a);

    cout << "TIM NGHICH DAO CUA b = " << test_b << " TRONG GF(2^10)" << endl;
    thuc_thi_euclidean_mo_rong(m_da_thuc, test_b);

    return 0;
}