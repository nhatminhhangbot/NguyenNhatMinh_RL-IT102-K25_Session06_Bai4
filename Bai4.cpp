#include <stdio.h>
#include <string.h>

int main() {
    char maSach[100][20];
    char tenSach[100][100];
    int tongSoLuong[100];
    int dangMuon[100];
    float giaBia[100];
    int soLuong = 0;
    int choice;

    do {
        printf("================ HE THONG QUAN LY KHO SACH ================\n");
        printf("1. Them dau sach moi vao kho\n");
        printf("2. Hien thi danh sach kho sach\n");
        printf("3. Ghi nhan Muon / Tra sach va tinh phi phat\n");
        printf("4. Xoa dau sach khoi he thong kho\n");
        printf("5. Thong ke tong gia tri tai san kho sach\n");
        printf("0. Thoat chuong trinh\n");
        printf("===========================================================\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        printf("\n");

        if (choice == 1) {
            if (soLuong >= 100) {
                printf("Kho day!\n");
            } else {
                char tempMa[20];
                printf("=== Lua chon 1: Them dau sach moi ===\n");
                printf("Nhap ma sach: ");
                scanf("%s", tempMa);
                
                int trung = 0;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], tempMa) == 0) {
                        trung = 1;
                        break;
                    }
                }
                
                if (trung) {
                    printf("Ma sach da ton tai!\n");
                } else {
                    strcpy(maSach[soLuong], tempMa);
                    while (getchar() != '\n');
                    printf("Nhap ten sach: ");
                    fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);
                    size_t len = strlen(tenSach[soLuong]);
                    if (len > 0 && tenSach[soLuong][len - 1] == '\n') {
                        tenSach[soLuong][len - 1] = '\0';
                    }
                    
                    int sl, hopLe = 0;
                    do {
                        printf("Nhap tong so luong: ");
                        scanf("%d", &sl);
                        if (sl > 0) {
                            tongSoLuong[soLuong] = sl;
                            hopLe = 1;
                        } else {
                            printf("So luong phai > 0!\n");
                        }
                    } while (!hopLe);
                    
                    float gb;
                    hopLe = 0;
                    do {
                        printf("Nhap gia bia (VND): ");
                        scanf("%f", &gb);
                        if (gb > 0) {
                            giaBia[soLuong] = gb;
                            hopLe = 1;
                        } else {
                            printf("Gia bia phai > 0!\n");
                        }
                    } while (!hopLe);
                    
                    dangMuon[soLuong] = 0;
                    soLuong++;
                    printf("Them dau sach moi thanh cong!\n");
                }
            }
            printf("\n");
        } else if (choice == 2) {
            printf("=== Lua chon 2: Hien thi danh sach kho sach ===\n");
            if (soLuong == 0) {
                printf("Kho sach hien dang rong!\n");
            } else {
                printf("--------------------------------------------------------------------------------------------------\n");
                printf("STT | Ma Sach | Ten Sach                 | Tong SL | Dang Muon | Kha Dung | Gia Bia (VND)\n");
                printf("--------------------------------------------------------------------------------------------------\n");
                for (int i = 0; i < soLuong; i++) {
                    int khaDung = tongSoLuong[i] - dangMuon[i];
                    printf("%-3d | %-7s | %-24s | %-7d | %-9d | %-8d | %.2f\n", 
                           i + 1, maSach[i], tenSach[i], tongSoLuong[i], dangMuon[i], khaDung, giaBia[i]);
                }
                printf("--------------------------------------------------------------------------------------------------\n");
            }
            printf("\n");
        } else if (choice == 3) {
            printf("=== Lua chon 3: Muon / Tra sach ===\n");
            char tempMa[20];
            printf("Nhap ma sach can thao tac: ");
            scanf("%s", tempMa);
            
            int pos = -1;
            for (int i = 0; i < soLuong; i++) {
                if (strcmp(maSach[i], tempMa) == 0) {
                    pos = i;
                    break;
                }
            }
            
            if (pos == -1) {
                printf("Khong tim thay sach!\n");
            } else {
                printf("Tim thay sach: %s (Dang muon: %d)\n", tenSach[pos], dangMuon[pos]);
                int thaoTac;
                printf("Chon thao tac (1 - Muon sach, 2 - Tra sach): ");
                scanf("%d", &thaoTac);
                
                if (thaoTac == 1) {
                    int slMuon;
                    printf("Nhap so luong muon: ");
                    scanf("%d", &slMuon);
                    int khaDung = tongSoLuong[pos] - dangMuon[pos];
                    if (slMuon > 0 && slMuon <= khaDung) {
                        dangMuon[pos] += slMuon;
                        printf("Muon sach thanh cong!\n");
                    } else {
                        printf("So luong muon khong hop le hoac vuot qua kha dung!\n");
                    }
                } else if (thaoTac == 2) {
                    int slTra, soNgayQuaHan;
                    printf("Nhap so luong tra: ");
                    scanf("%d", &slTra);
                    printf("Nhap so ngay qua han (0 neu dung han): ");
                    scanf("%d", &soNgayQuaHan);
                    
                    if (slTra > 0 && slTra <= dangMuon[pos]) {
                        dangMuon[pos] -= slTra;
                        long long tienPhat = 0;
                        if (soNgayQuaHan > 0) {
                            tienPhat = (long long)slTra * soNgayQuaHan * 5000;
                        }
                        printf("\n--- BIEN NHAN TRA SACH ---\n");
                        printf("Tra thanh cong: %d quyen.\n", slTra);
                        printf("Phat hien qua han: %d ngay.\n", soNgayQuaHan);
                        printf("Tien phat qua han (5.000 VND/quyen/ngay): %lld VND.\n", tienPhat);
                    } else {
                        printf("So luong tra khong hop le!\n");
                    }
                } else {
                    printf("Thao tac khong hop le!\n");
                }
            }
            printf("\n");
        } else if (choice == 4) {
            printf("=== Lua chon 4: Xoa dau sach khoi he thong kho ===\n");
            char tempMa[20];
            printf("Nhap ma sach can xoa: ");
            scanf("%s", tempMa);
            
            int pos = -1;
            for (int i = 0; i < soLuong; i++) {
                if (strcmp(maSach[i], tempMa) == 0) {
                    pos = i;
                    break;
                }
            }
            
            if (pos == -1) {
                printf("Khong tim thay sach!\n");
            } else {
                if (dangMuon[pos] > 0) {
                    printf("Sach dang cho muon, khong the xoa khoi he thong!\n");
                } else {
                    for (int i = pos; i < soLuong - 1; i++) {
                        strcpy(maSach[i], maSach[i + 1]);
                        strcpy(tenSach[i], tenSach[i + 1]);
                        tongSoLuong[i] = tongSoLuong[i + 1];
                        dangMuon[i] = dangMuon[i + 1];
                        giaBia[i] = giaBia[i + 1];
                    }
                    soLuong--;
                    printf("Xoa dau sach thanh cong!\n");
                }
            }
            printf("\n");
        } else if (choice == 5) {
            printf("=== Lua chon 5: Thong ke tong gia tri tai san kho sach ===\n");
            if (soLuong == 0) {
                printf("Kho sach hien dang rong!\n");
            } else {
                int tongBanSach = 0;
                int tongDangMuon = 0;
                double tongGiaTri = 0;
                for (int i = 0; i < soLuong; i++) {
                    tongBanSach += tongSoLuong[i];
                    tongDangMuon += dangMuon[i];
                    tongGiaTri += (double)tongSoLuong[i] * giaBia[i];
                }
                printf("Tong so dau sach: %d\n", soLuong);
                printf("Tong so ban sach: %d\n", tongBanSach);
                printf("Tong so sach dang muon: %d\n", tongDangMuon);
                printf("Tong gia tri tai san kho sach: %.2f VND\n", tongGiaTri);
            }
            printf("\n");
        } else if (choice == 0) {
            printf("Thoat chuong trinh.\n");
        } else {
            printf("Lua chon khong hop le!\n\n");
        }
    } while (choice != 0);

    return 0;
}
