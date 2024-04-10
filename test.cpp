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
            i--; // 重新生成这个题目
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
    return a; // 默认返回a，避免编译器警告
}

void generate_fourth_to_sixth_grade(int num, int max_value) {
    for (int i = 0; i < num; i++) {
        int values[4];
        char ops[3];
        char ops_choices[] = {'+', '-', '*', '/'};
        int result, pos;

        // 生成随机数值和运算符
        for (int j = 0; j < 4; j++) {
            values[j] = rand() % max_value + 1;
        }
        for (int j = 0; j < 3; j++) {
            ops[j] = ops_choices[rand() % 4];
        }

        // 选择括号位置
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

extern int perform_operation(int a, int b, char op);  // 假设这个函数在另一个文件中定义

TEST(MathTest, PerformOperation) {
    // 测试加法
    EXPECT_EQ(perform_operation(5, 3, '+'), 8);

    // 测试减法
    EXPECT_EQ(perform_operation(5, 3, '-'), 2);

    // 测试乘法
    EXPECT_EQ(perform_operation(5, 3, '*'), 15);

    // 测试除法
    EXPECT_EQ(perform_operation(6, 3, '/'), 2);

    // 测试除数为零的情况
    EXPECT_EQ(perform_operation(5, 0, '/'), 5);  // 假设您的函数定义了除以零返回第一个操作数
}

int fake_rand() {
    static int calls = 0;
    return calls++ % 20;  // 返回一个可预测的序列
}

TEST(GradeTest, GenerateFirstGrade) {
    std::streambuf* original_buf = std::cout.rdbuf();  // 保存原始缓冲区
    std::stringstream buffer;  // 创建一个stringstream来捕获输出
    std::cout.rdbuf(buffer.rdbuf());  // 重定向cout到buffer

    srand(1);  // 为rand()设置种子，使测试具有可预测性
    generate_first_grade(5);  // 生成5个题目

    // 恢复标准输出
    std::cout.rdbuf(original_buf);

    // 检查生成的输出
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
    std::streambuf* original_buf = std::cout.rdbuf();  // 保存原始缓冲区
    std::stringstream buffer;  // 创建一个stringstream来捕获输出
    std::cout.rdbuf(buffer.rdbuf());  // 重定向cout到buffer

    generate_second_grade(5);  // 生成5个题目

    // 恢复标准输出
    std::cout.rdbuf(original_buf);

    // 检查生成的输出
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
    std::streambuf* original_buf = std::cout.rdbuf();  // 保存原始缓冲区
    std::stringstream buffer;  // 创建一个stringstream来捕获输出
    std::cout.rdbuf(buffer.rdbuf());  // 重定向cout到buffer

    generate_third_grade(5);  // 生成5个题目

    // 恢复标准输出
    std::cout.rdbuf(original_buf);

    // 检查生成的输出
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

        // 根据操作符验证结果的范围
        if (op == '+') {
            EXPECT_GE(a + b, 0);
            // 可以添加更多的逻辑来验证加法的特定约束
        }
        else if (op == '-') {
            EXPECT_GE(a - b, 0);
            // 可以添加更多的逻辑来验证减法的特定约束
        }
        else if (op == '*') {
            EXPECT_GE(a * b, 0);
            // 可以添加更多的逻辑来验证乘法的特定约束
        }
        else {
            FAIL() << "Invalid operator";
        }
    }
}

TEST(GradeTest, GenerateFourthToSixthGrade) {
    int max_value = 100; // 示例，可以根据具体年级调整
    std::streambuf* original_buf = std::cout.rdbuf();  // 保存原始缓冲区
    std::stringstream buffer;  // 创建一个stringstream来捕获输出
    std::cout.rdbuf(buffer.rdbuf());  // 重定向cout到buffer

    generate_fourth_to_sixth_grade(5, max_value);  // 生成5个题目

    // 恢复标准输出
    std::cout.rdbuf(original_buf);

    // 检查生成的输出
    std::string line;
    while (std::getline(buffer, line)) {
        // 此处应有逻辑解析输出的数学题，并验证
        // 由于这个函数生成的表达式更复杂，包括括号和四种操作符
        // 因此需要更复杂的解析逻辑来验证每个生成的题目
        // 这可能包括解析表达式、执行计算和检查结果

        // 例如，简单检查输出格式和操作数范围
        EXPECT_FALSE(line.empty());  // 确保输出不为空
        // 更多的检查应当添加，例如解析表达式并计算结果，
        // 然后与预期结果进行比较
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
