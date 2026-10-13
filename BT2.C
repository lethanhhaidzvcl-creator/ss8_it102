
#include <stdio.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    int monthly_fee;
    int penalty_fee;
};

int main() {
    struct UserAccount users[100];
    int n, i;
    int total_revenue = 0;
    int downgraded_count = 0;

    do {
        printf("Nhap so luong tai khoan (1-100): ");
        if (scanf("%d", &n) != 1) {
            printf("Du lieu khong hop le!\n");
            while (getchar() != '\n');
            n = 0;
        } else if (n < 1 || n > 100) {
            printf("So luong phai tu 1 den 100!\n");
        }
    } while (n < 1 || n > 100);

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap tai khoan %d ---\n", i + 1);

        do {
            printf("Ma tai khoan: ");
            if (scanf("%d", &users[i].user_id) != 1) {
                printf("Ma tai khoan phai la so nguyen!\n");
                while (getchar() != '\n');
                users[i].user_id = 0;
            } else if (users[i].user_id <= 0) {
                printf("Ma tai khoan phai lon hon 0!\n");
            }
        } while (users[i].user_id <= 0);

        printf("Ten tai khoan (khong dau cach): ");
        scanf("%49s", users[i].username);

        do {
            printf("Loai goi (1-Free, 2-Personal, 3-Family): ");
            if (scanf("%d", &users[i].plan_type) != 1) {
                printf("Loai goi phai la so nguyen!\n");
                while (getchar() != '\n');
                users[i].plan_type = 0;
            } else if (users[i].plan_type < 1 ||
                       users[i].plan_type > 3) {
                printf("Loai goi chi duoc tu 1 den 3!\n");
            }
        } while (users[i].plan_type < 1 ||
                 users[i].plan_type > 3);

        do {
            printf("So ngay no cuoc: ");
            if (scanf("%d", &users[i].days_overdue) != 1) {
                printf("So ngay no phai la so nguyen!\n");
                while (getchar() != '\n');
                users[i].days_overdue = -1;
            } else if (users[i].days_overdue < 0) {
                printf("So ngay no khong duoc am!\n");
            }
        } while (users[i].days_overdue < 0);

        do {
            printf("So thiet bi dang ket noi: ");
            if (scanf("%d", &users[i].active_devices) != 1) {
                printf("So thiet bi phai la so nguyen!\n");
                while (getchar() != '\n');
                users[i].active_devices = -1;
            } else if (users[i].active_devices < 0) {
                printf("So thiet bi khong duoc am!\n");
            }
        } while (users[i].active_devices < 0);

        users[i].penalty_fee = 0;

        if (users[i].plan_type == 1) {
            users[i].monthly_fee = 0;
        } else if (users[i].plan_type == 2) {
            users[i].monthly_fee = 120000;
        } else {
            users[i].monthly_fee = 250000;
        }
    }

    for (i = 0; i < n; i++) {
        if (users[i].days_overdue >= 3) {
            if (users[i].plan_type != 1) {
                downgraded_count++;
            }

            users[i].plan_type = 1;
            users[i].monthly_fee = 0;
            users[i].penalty_fee = 0;
        } else if (users[i].plan_type == 2 &&
                   users[i].active_devices > 1) {
            users[i].penalty_fee =
                (users[i].active_devices - 1) * 30000;
        }

        total_revenue += users[i].monthly_fee
                       + users[i].penalty_fee;
    }

    printf("\n========== BAO CAO DOI SOAT TAI KHOAN ==========\n");
    printf("%-10s %-20s %-10s %-12s %-12s %-20s\n",
           "Ma TK", "Ten TK", "Ma Goi",
           "So Thiet Bi", "So Ngay No", "Phi Thuc Thu");

    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-20s %-10d %-12d %-12d %-20d\n",
               users[i].user_id,
               users[i].username,
               users[i].plan_type,
               users[i].active_devices,
               users[i].days_overdue,
               users[i].monthly_fee + users[i].penalty_fee);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Tong doanh thu thuc thu: %d VND\n", total_revenue);
    printf("So tai khoan bi ha cap: %d\n", downgraded_count);

    return 0;
}
