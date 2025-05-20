#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>

int count_month_days(int m, int yr) {
    int d;
    d = 31;
    if (m == 4) d = 30;
    if (m == 6) d = 30;
    if (m == 9) d = 30;
    if (m == 11) d = 30;
    if (m == 2) {
        if (yr % 4 == 0) d = 29;
        else d = 28;
    }
    return d;
}

void show_day(int wd) {
    if (wd == 0) printf("�����������");
    if (wd == 1) printf("�����������");
    if (wd == 2) printf("�������");
    if (wd == 3) printf("�����");
    if (wd == 4) printf("�������");
    if (wd == 5) printf("�������");
    if (wd == 6) printf("�������");
}

void show_month(int m) {
    if (m == 1) printf("������");
    if (m == 2) printf("�������");
    if (m == 3) printf("����");
    if (m == 4) printf("������");
    if (m == 5) printf("���");
    if (m == 6) printf("����");
    if (m == 7) printf("����");
    if (m == 8) printf("������");
    if (m == 9) printf("��������");
    if (m == 10) printf("�������");
    if (m == 11) printf("������");
    if (m == 12) printf("�������");
}

int find_day(int yr, int m, int d) {
    struct tm t;
    t.tm_year = yr - 1900;
    t.tm_mon = m - 1;
    t.tm_mday = d;
    t.tm_hour = 12;
    t.tm_min = 0;
    t.tm_sec = 0;
    mktime(&t);
    return t.tm_wday;
}

void display_month(int yr, int m) {
    int start, max_days, curr, spaces;
    show_month(m);
    printf(" %d\n", yr);
    printf("�� �� �� �� �� �� ��\n");
    start = find_day(yr, m, 0);
    max_days = count_month_days(m, yr);
    spaces = start;
    curr = 1;
    while (spaces > 0) {
        printf("   ");
        spaces = spaces - 1;
    }
    while (curr <= max_days) {
        printf("%2d ", curr);
        if ((curr + start) % 7 == 0){
        	printf("\n");
		}
        curr = curr + 1;
    }
    printf("\n");
    printf("====================\n");
    printf("\n");
}

void display_year(int yr) {
    int m;
    m = 1;
    while (m <= 12) {
        display_month(yr, m);
        m = m + 1;
    }
}

void show_today()
{
    time_t mytime = time(NULL);
    struct tm *now = localtime(&mytime);
    if(now->tm_mon < 10){
    	printf("����: %d.0%d.%d\n", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    	printf("�����: %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);
	}
	else{
    printf("����: %d.%d.%d\n", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    printf("�����: %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);
    return 0;
	}
}

int main() {
	char locale = setlocale(LC_ALL, "");
    char buf[15];
    int yr, m, d, n;
    printf("������� ���� (����.��.�� || ����.�� || ���� ��� now): ");
    scanf("%s", buf);
    if (strcmp(buf, "now") == 0) {
        show_today();
        return 0;
    }
    n = sscanf(buf, "%d.%d.%d", &yr, &m, &d);
    if (n == 3) {
            int wd;
            wd = find_day(yr, m, d);
            printf("����: %d.%d.%d - ", yr, m, d);
            show_day(wd);
            printf("\n");
            return 0;
        }
        
    n = sscanf(buf, "%d.%d", &yr, &m);
    if (n == 2) {
        display_month(yr, m);
        return 0;
    }
    n = sscanf(buf, "%d", &yr);
    if (n == 1) {
    	printf("\n");
        display_year(yr);
        return 0;
    }
    printf("������!!!\n");
    return 0;
}
