//
// Created by lWoHvYe on 2023/3/26.
//

#include <stdio.h>
#include <math.h>
#include "loan.h"

void loan_business() {
    double d; // 贷款额度
    double p; // 每月还款额
    double yr; // 年利率
    double r; // 月利率
    double m; // 还款月数


    printf("请输入... d,p,yr 注:d=贷款额度,p=每月还款额,yr=年利率%%(百分之)\n");
    scanf("%lf,%lf,%lf", &d, &p, &yr);

    r = yr / 12 / 100; // 转成月利率，并转成百分比

    m = (log10(p) - log10(p - d * r)) / (log10(1 + r));

    printf("%lf %lf\n", pow(10, m * log10(1 + r)) * (p - d * r), p);

    printf("It need %lf month to clear %lf with %lf peer month\n", m, d, p);
}