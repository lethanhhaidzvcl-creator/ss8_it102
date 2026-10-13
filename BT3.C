
#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    struct UserAccount users[100];
    struct UserAccount temp;
    int n, i, j;
    int mrr_before = 0;
    int mrr_after = 0;
    int difference;

    do {
        printf("Nhap so luong tai khoan (1-100): ");

        if (scanf("%d", &n) != 1) {
            printf("Du lieu khong hop le!\n");
            while (getchar() != '\n');
            n = 0;
        } else if (n < 1 || n > 100) {
            printf("N phai tu 1 den 100!\n");
        }
    } while (n < 1 || n > 100);

    for (i = 0; i < n; i++) {
        printf("\n--- Tai khoan %d ---\n", i + 1);

        printf("Ma tai khoan: ");
        scanf("%d", &users[i].account_id);

        do {
            printf("Loai goi (0-Free, 1-Standard, 2-Premium): ");

            if (scanf("%d", &users[i].plan_type) != 1) {
                printf("Loai goi phai la so nguyen!\n");
                while (getchar() != '\n');
                users[i].plan_type = -1;
            } else if (users[i].plan_type < 0 ||
                       users[i].plan_type > 2) {
                printf("Loai goi khong hop le!\n");
            }
        } while (users[i].plan_type < 0 ||
                 users[i].plan_type > 2);

        printf("Phi thang hien tai: ");
        scanf("%d", &users[i].monthly_fee);

        printf("So ngay con lai: ");
        scanf("%d", &users[i].remaining_days);

        printf("So thiet bi dang ket noi: ");
        scanf("%d", &users[i].active_devices);

        mrr_before += users[i].monthly_fee;
    }

    for (i = 0; i < n; i++) {
        /* Het han: ha cap ve Free */
        if (users[i].remaining_days <= 0) {
            users[i].plan_type = 0;
            users[i].monthly_fee = 0;
        }

        if (users[i].active_devices <= 0) {
            users[i].active_devices = 1;
        }

        if (users[i].plan_type == 0) {
            users[i].monthly_fee = 0;

            if (users[i].active_devices > 1) {
                users[i].active_devices = 1;
            }
        } else if (users[i].plan_type == 1) {
            users[i].monthly_fee = 120000;

            if (users[i].active_devices > 2) {
                users[i].active_devices = 2;
            }
        } else {
            users[i].monthly_fee = 300000;

            if (users[i].active_devices > 5) {
                users[i].active_devices = 5;
            }
        }

        mrr_after += users[i].monthly_fee;
    }

    for (i = 1; i < n; i++) {
        temp = users[i];
        j = i - 1;

        while (j >= 0 &&
               ((users[j].plan_type == 0 &&
                 temp.plan_type > 0) ||
                (users[j].plan_type > 0 &&
                 temp.plan_type > 0 &&
                 users[j].monthly_fee < temp.monthly_fee))) {
            users[j + 1] = users[j];
            j--;
        }

        users[j + 1] = temp;
    }

    printf("\n=============== BAO CAO KIEM TOAN ===============\n");
    printf("%-10s %-10s %-12s %-15s %-15s\n",
           "Ma TK", "Ma goi", "Phi thang",
           "Ngay con lai", "So thiet bi");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-10d %-12d %-15d %-15d\n",
               users[i].account_id,
               users[i].plan_type,
               users[i].monthly_fee,
               users[i].remaining_days,
               users[i].active_devices);
    }

    difference = mrr_after - mrr_before;

    printf("---------------------------------------------------------------\n");
    printf("MRR truoc kiem toan: %d VND\n", mrr_before);
    printf("MRR sau kiem toan:   %d VND\n", mrr_after);
    printf("Chenh lech MRR:      %d VND\n", difference);

    return 0;
}
