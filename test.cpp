#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_first_grade(int num) {
    for (int i = 0; i < num; i++) {
        int a = rand() % 20;
        int b = rand() % 20;
        char op = (rand() % 2 == 0) ? '+' : '-';
        int result = (op == '+') ? a + b : a - b;
        if (result >= 0 && result < 20) {
            printf("%d %c %d = \n", a, op, b);
        } else {
            i--; // �������������Ŀ
        }
    }
}

void generate_second_grade(int num) {
    for (int i = 0; i < num; i++) {
        int a = rand() % 50;
        int b = rand() % 50;
        char op = (rand() % 2 == 0) ? '+' : '-';
        int result = (op == '+') ? a + b : a - b;
        if (result >= 0 && result < 50) {
            printf("%d %c %d = \n", a, op, b);
        } else {
            i--;
        }
    }
}

void generate_third_grade(int num) {
    for (int i = 0; i < num; i++) {
        int a = rand() % 1000;
        int b = rand() % 1000;
        char ops[] = {'+', '-', '*'};
        char op = ops[rand() % 3];
        int result;
        switch (op) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
        }
        printf("%d %c %d = \n", a, op, b);
    }
}

int perform_operation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : a;
    }
    return a; // Ĭ�Ϸ���a���������������
}

void generate_fourth_to_sixth_grade(int num, int max_value) {
    for (int i = 0; i < num; i++) {
        int values[4];
        char ops[3];
        char ops_choices[] = {'+', '-', '*', '/'};
        int result, pos;

        // ���������ֵ�������
        for (int j = 0; j < 4; j++) {
            values[j] = rand() % max_value + 1;
        }
        for (int j = 0; j < 3; j++) {
            ops[j] = ops_choices[rand() % 4];
        }

        // ѡ������λ��
        pos = rand() % 3;

        do {
            for (int j = 0; j < 4; j++) {
                values[j] = rand() % max_value + 1;
            }

            switch (pos) {
                case 0:
                    result = perform_operation(perform_operation(values[0], values[1], ops[0]), values[2], ops[1]);
                    result = perform_operation(result, values[3], ops[2]);
                    break;
                case 1:
                    result = perform_operation(values[0], perform_operation(values[1], values[2], ops[1]), ops[0]);
                    result = perform_operation(result, values[3], ops[2]);
                    break;
                case 2:
                    result = perform_operation(values[0], values[1], ops[0]);
                    result = perform_operation(result, perform_operation(values[2], values[3], ops[2]), ops[1]);
                    break;
            }
        } while (result < 0);

        switch (pos) {
            case 0:
                printf("(%d %c %d) %c %d %c %d = \n", values[0], ops[0], values[1], ops[1], values[2], ops[2], values[3]);
                break;
            case 1:
                printf("%d %c (%d %c %d) %c %d = \n", values[0], ops[0], values[1], ops[1], values[2], ops[2], values[3]);
                break;
            case 2:
                printf("%d %c %d %c (%d %c %d) = \n", values[0], ops[0], values[1], ops[1], values[2], ops[2], values[3]);
                break;
        }
    }
}



#include <gtest/gtest.h>

extern int perform_operation(int a, int b, char op);  // ���������������һ���ļ��ж���

TEST(MathTest, PerformOperation) {
    // ���Լӷ�
    EXPECT_EQ(perform_operation(5, 3, '+'), 8);

    // ���Լ���
    EXPECT_EQ(perform_operation(5, 3, '-'), 2);

    // ���Գ˷�
    EXPECT_EQ(perform_operation(5, 3, '*'), 15);

    // ���Գ���
    EXPECT_EQ(perform_operation(6, 3, '/'), 2);

    // ���Գ���Ϊ������
    EXPECT_EQ(perform_operation(5, 0, '/'), 5);  // �������ĺ��������˳����㷵�ص�һ��������
}

int fake_rand() {
    static int calls = 0;
    return calls++ % 20;  // ����һ����Ԥ�������
}

TEST(GradeTest, GenerateFirstGrade) {
    std::streambuf* original_buf = std::cout.rdbuf();  // ����ԭʼ������
    std::stringstream buffer;  // ����һ��stringstream���������
    std::cout.rdbuf(buffer.rdbuf());  // �ض���cout��buffer

    srand(1);  // Ϊrand()�������ӣ�ʹ���Ծ��п�Ԥ����
    generate_first_grade(5);  // ����5����Ŀ

    // �ָ���׼���
    std::cout.rdbuf(original_buf);

    // ������ɵ����
    std::string line;
    while (std::getline(buffer, line)) {
        int a, b;
        char op;
        std::istringstream iss(line);
        if (!(iss >> a >> op >> b)) {
            FAIL() << "Invalid output format";
        }
        EXPECT_GE(a, 0);
        EXPECT_LT(a, 20);
        EXPECT_GE(b, 0);
        EXPECT_LT(b, 20);
        if (op == '+') {
            EXPECT_GE(a + b, 0);
            EXPECT_LT(a + b, 20);
        }
        else if (op == '-') {
            EXPECT_GE(a - b, 0);
            EXPECT_LT(a - b, 20);
        }
        else {
            FAIL() << "Invalid operator";
        }
    }
}

TEST(GradeTest, GenerateSecondGrade) {
    std::streambuf* original_buf = std::cout.rdbuf();  // ����ԭʼ������
    std::stringstream buffer;  // ����һ��stringstream���������
    std::cout.rdbuf(buffer.rdbuf());  // �ض���cout��buffer

    generate_second_grade(5);  // ����5����Ŀ

    // �ָ���׼���
    std::cout.rdbuf(original_buf);

    // ������ɵ����
    std::string line;
    while (std::getline(buffer, line)) {
        int a, b;
        char op;
        std::istringstream iss(line);
        if (!(iss >> a >> op >> b)) {
            FAIL() << "Invalid output format";
        }
        EXPECT_GE(a, 0);
        EXPECT_LT(a, 50);
        EXPECT_GE(b, 0);
        EXPECT_LT(b, 50);
        if (op == '+') {
            EXPECT_GE(a + b, 0);
            EXPECT_LT(a + b, 50);
        }
        else if (op == '-') {
            EXPECT_GE(a - b, 0);
            EXPECT_LT(a - b, 50);
        }
        else {
            FAIL() << "Invalid operator";
        }
    }
}

TEST(GradeTest, GenerateThirdGrade) {
    std::streambuf* original_buf = std::cout.rdbuf();  // ����ԭʼ������
    std::stringstream buffer;  // ����һ��stringstream���������
    std::cout.rdbuf(buffer.rdbuf());  // �ض���cout��buffer

    generate_third_grade(5);  // ����5����Ŀ

    // �ָ���׼���
    std::cout.rdbuf(original_buf);

    // ������ɵ����
    std::string line;
    while (std::getline(buffer, line)) {
        int a, b;
        char op;
        std::istringstream iss(line);
        if (!(iss >> a >> op >> b)) {
            FAIL() << "Invalid output format";
        }
        EXPECT_GE(a, 0);
        EXPECT_LT(a, 1000);
        EXPECT_GE(b, 0);
        EXPECT_LT(b, 1000);

        // ���ݲ�������֤����ķ�Χ
        if (op == '+') {
            EXPECT_GE(a + b, 0);
            // ������Ӹ�����߼�����֤�ӷ����ض�Լ��
        }
        else if (op == '-') {
            EXPECT_GE(a - b, 0);
            // ������Ӹ�����߼�����֤�������ض�Լ��
        }
        else if (op == '*') {
            EXPECT_GE(a * b, 0);
            // ������Ӹ�����߼�����֤�˷����ض�Լ��
        }
        else {
            FAIL() << "Invalid operator";
        }
    }
}

TEST(GradeTest, GenerateFourthToSixthGrade) {
    int max_value = 100; // ʾ�������Ը��ݾ����꼶����
    std::streambuf* original_buf = std::cout.rdbuf();  // ����ԭʼ������
    std::stringstream buffer;  // ����һ��stringstream���������
    std::cout.rdbuf(buffer.rdbuf());  // �ض���cout��buffer

    generate_fourth_to_sixth_grade(5, max_value);  // ����5����Ŀ

    // �ָ���׼���
    std::cout.rdbuf(original_buf);

    // ������ɵ����
    std::string line;
    while (std::getline(buffer, line)) {
        // �˴�Ӧ���߼������������ѧ�⣬����֤
        // ��������������ɵı��ʽ�����ӣ��������ź����ֲ�����
        // �����Ҫ�����ӵĽ����߼�����֤ÿ�����ɵ���Ŀ
        // ����ܰ����������ʽ��ִ�м���ͼ����

        // ���磬�򵥼�������ʽ�Ͳ�������Χ
        EXPECT_FALSE(line.empty());  // ȷ�������Ϊ��
        // ����ļ��Ӧ����ӣ�����������ʽ����������
        // Ȼ����Ԥ�ڽ�����бȽ�
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
