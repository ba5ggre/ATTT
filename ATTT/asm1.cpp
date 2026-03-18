#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Hàm khởi tạo ma trận 5x5 từ từ khóa
void generateMatrix(char key[], char matrix[SIZE][SIZE]) {
    int dict[26] = {0};
    int i, j, k = 0, len = strlen(key);
    
    // Đánh dấu các chữ cái trong từ khóa (coi I và J là một) 
    for (i = 0; i < len; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z' && dict[c - 'A'] == 0) {
            matrix[k / SIZE][k % SIZE] = c;
            dict[c - 'A'] = 1;
            if (c == 'I') dict['J' - 'A'] = 1;
            k++;
        }
    }
    
    // Điền nốt các chữ cái còn lại trong bảng chữ cái [cite: 178]
    for (i = 0; i < 26; i++) {
        if (dict[i] == 0) {
            char c = i + 'A';
            if (c == 'J') continue;
            matrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
}

// Tìm vị trí của ký tự trong ma trận
void findPosition(char matrix[SIZE][SIZE], char c, int *row, int *col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Hàm mã hóa Playfair [cite: 184]
void encrypt(char text[], char matrix[SIZE][SIZE]) {
    int i, r1, c1, r2, c2;
    int len = strlen(text);

    for (i = 0; i < len; i += 2) {
        findPosition(matrix, text[i], &r1, &c1);
        findPosition(matrix, text[i+1], &r2, &c2);

        if (r1 == r2) { // Cùng hàng: dịch phải [cite: 187, 195]
            text[i] = matrix[r1][(c1 + 1) % SIZE];
            text[i+1] = matrix[r2][(c2 + 1) % SIZE];
        } else if (c1 == c2) { // Cùng cột: dịch xuống [cite: 188, 197]
            text[i] = matrix[(r1 + 1) % SIZE][c1];
            text[i+1] = matrix[(r2 + 1) % SIZE][c2];
        } else { // Hình chữ nhật: tráo cột [cite: 189, 199]
            text[i] = matrix[r1][c2];
            text[i+1] = matrix[r2][c1];
        }
    }
}

int main() {
    char matrix[SIZE][SIZE];
    char key[] = "MONARCHY"; // Ví dụ từ tài liệu [cite: 176]
    char rawText[] = "BALLOON";
    char preparedText[100] = "";
    int i, j = 0;

    generateMatrix(key, matrix);

    // Chuẩn bị bản rõ: viết hoa và xử lý cặp trùng [cite: 185, 194]
    for (i = 0; i < strlen(rawText); i++) {
        char c = toupper(rawText[i]);
        if (c < 'A' || c > 'Z') continue;
        preparedText[j++] = c;
        if (i < strlen(rawText) - 1 && c == toupper(rawText[i+1])) {
            preparedText[j++] = 'X'; // Chèn X nếu 2 chữ giống nhau [cite: 186]
        }
    }
    if (j % 2 != 0) preparedText[j++] = 'X'; // Thêm X nếu độ dài lẻ
    preparedText[j] = '\0';

    printf("Ban ro da xu ly: %s\n", preparedText);
    encrypt(preparedText, matrix);
    printf("Ban ma Playfair: %s\n", preparedText);

    return 0;
}