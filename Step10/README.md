# Step10 : 메모리 사용량 예측기 (CSV 기반 + 자동 측정)

- `/proc/meminfo`에서 현재 메모리 사용량을 읽어와 csv 기록에 추가

- 이전 7일 데이터 + 오늘 데이터를 기반으로 **선형 회귀** 로 7일 예측

## 실습 코드

1. **csv 파일**

   ```
   day,usage
   0,31.2
   1,32.8
   2,34.0
   3,35.1
   4,36.0
   5,37.4
   6,38.9
   ```

   <br/>

2. 메모리 측정: Step09

   ```c
   double today_usage = get_memory_usage_percent();
   if (today_usage < 0) {
        fprintf(stderr, "메모리 사용량 측정 실패\n");
        return 1;
   }
   ```

   <br/>

3. **선형회귀**

   ```c
   double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

   for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
   }

   double a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
   double b = (sum_y - a * sum_x) / n;
   ```

## 출력

```
오늘의 메모리 사용량: 18.02%
Linear Regression: y = -0.60x + 35.04

예측 메모리 사용량 (다음 7일):
  day 8: 30.22%
  day 9: 29.61%
  day 10: 29.01%
  day 11: 28.41%
  day 12: 27.80%
  day 13: 27.20%
  day 14: 26.60%
```


