# 2308.11307v1 - Algorithm 1 Reproduction Starter

이 폴더는 해당 논문의 **Algorithm 1 (randomized interval DP for 0-1 knapsack)** 을 먼저 구현하고,
고전적인 0-1 knapsack DP와 시간 비교를 하기 위한 시작점이다.

## 폴더 구조

```text
2308.11307v1/
├─ CMakeLists.txt
├─ README.md
├─ include/
│  ├─ common/
│  │  ├─ csv.hpp
│  │  ├─ random_instance.hpp
│  │  ├─ timer.hpp
│  │  └─ types.hpp
│  └─ solvers/
│     ├─ alg1_interval_dp.hpp
│     └─ zero_one_dp.hpp
├─ src/
│  └─ solvers/
│     ├─ alg1_interval_dp.cpp
│     └─ zero_one_dp.cpp
├─ apps/
│  ├─ benchmark_alg1.cpp
│  └─ test_alg1.cpp
├─ scripts/
│  └─ plot_alg1.py
├─ data/
└─ figures/
```

## 현재 들어 있는 것

- `zero_one_dp.*`  
  고전적인 exact 0-1 knapsack DP (`O(nW)`) baseline

- `alg1_interval_dp.*`  
  논문 1번 알고리즘의 시작 구현

- `test_alg1.cpp`  
  작은 랜덤 인스턴스에서 exact DP와 값 비교

- `benchmark_alg1.cpp`  
  CSV로 시간 측정 결과를 저장

- `plot_alg1.py`  
  CSV를 읽어서 그래프 PNG 생성

## 빌드

루트 폴더(`2308.11307v1/`)에서:

```bash
mkdir -p build
cd build
cmake ..
make -j
```

## 1. correctness test

예시:

```bash
./test_alg1
```

조금 더 크게:

```bash
./test_alg1 300 40 25 60 0.5 6.0
```

인자 순서:

```text
trials n w_max v_max capacity_ratio delta_factor
```

## 2. benchmark 실행

### (a) n 변화

```bash
./benchmark_alg1 by_n ../data/alg1_by_n.csv 5 6.0
```

### (b) w_max 변화

```bash
./benchmark_alg1 by_wmax ../data/alg1_by_wmax.csv 5 6.0
```

인자 순서:

```text
mode output_csv trials delta_factor
```

## 3. 그래프 그리기

Python 패키지:

```bash
pip install pandas matplotlib
```

실행:

```bash
python ../scripts/plot_alg1.py ../data/alg1_by_n.csv ../figures
python ../scripts/plot_alg1.py ../data/alg1_by_wmax.csv ../figures
```

## 실험 해석 시 주의

- Algorithm 1은 randomized algorithm이라 seed 영향을 받을 수 있다.
- `delta_factor` 는 구현 상수다. 값이 작으면 더 빠를 수 있지만 실패율이 오를 수 있다.
- 작은 입력에서는 baseline DP가 더 빠를 수 있다.
- correctness test를 충분히 돌린 뒤 benchmark를 보는 것이 좋다.

## 다음 단계

오늘 목표를 Algorithm 1에 한정한다면, 추천 순서는 다음과 같다.

1. `test_alg1`로 값 비교가 얼마나 맞는지 본다.
2. `delta_factor`를 조절해 본다.
3. `benchmark_alg1`로 CSV를 만든다.
4. `plot_alg1.py`로 그래프를 만든다.
5. README에 결과 그림을 붙인다.
6. 그 다음 Algorithm 2 폴더/파일을 같은 레포 안에 이어서 추가한다.
