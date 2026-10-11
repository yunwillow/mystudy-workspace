#include <stdio.h>

// 定义四个简单的数学运算函数
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0)
        return a / b;
    else {
        printf("Error: Division by zero.\n");
        return 0;
    }
}

// 使用 typedef 定义函数指针类型，简化后续声明
typedef int (*MathOperation)(int, int);

// 函数指针作为参数：实现通用的计算函数
void calculate(MathOperation op, int a, int b) {
    int result = op(a, b);  // 通过函数指针调用对应的函数
    printf("Result: %d\n", result);
}

// 函数指针数组：模拟菜单驱动的计算器
void menu_driven_calculator() {
    // 定义函数指针数组，索引对应菜单选项
    MathOperation operations[] = {add, subtract, multiply, divide};
    char *menu[] = {"Add", "Subtract", "Multiply", "Divide"};
    
    int choice, a, b;

    printf("=== Menu-Driven Calculator ===\n");
    printf("0: Add\n1: Subtract\n2: Multiply\n3: Divide\n");
    printf("Enter your choice (0-3): ");
    scanf("%d", &choice);

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    // 通过函数指针数组调用对应的运算
    if (choice >= 0 && choice <= 3) {
        int result = operations[choice](a, b);
        printf("Result of %s: %d\n", menu[choice], result);
    } else {
        printf("Invalid choice.\n");
    }
}

// 返回函数指针的函数：根据操作符选择对应的函数
MathOperation get_operation(char op) {
    switch (op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide;
        default: return NULL;
    }
}

int main() {
    // 示例1：基本函数指针的声明与调用
    {
        printf("=== Example 1: Basic Function Pointer ===\n");

        // 声明函数指针并赋值
        int (*operation)(int, int) = &add;  // 可以省略 &，直接 operation = add;

        // 通过函数指针调用函数
        int result = operation(5, 3);
        printf("5 + 3 = %d\n", result);

        // 改变指针指向的函数
        operation = subtract;
        result = operation(5, 3);
        printf("5 - 3 = %d\n", result);
    }

    // 示例2：函数指针作为参数
    {
        printf("\n=== Example 2: Function Pointer as Argument ===\n");
        calculate(add, 10, 5);       // 调用 add
        calculate(subtract, 10, 5);  // 调用 subtract
    }

    // 示例3：使用 typedef 简化函数指针类型
    {
        printf("\n=== Example 3: Using typedef for Function Pointer ===\n");
        MathOperation op1 = multiply;
        MathOperation op2 = divide;

        printf("4 * 3 = %d\n", op1(4, 3));
        printf("8 / 2 = %d\n", op2(8, 2));
    }

    // 示例4：函数指针数组（菜单驱动）
    {
        printf("\n=== Example 4: Function Pointer Array (Menu-Driven) ===\n");
        menu_driven_calculator();
    }

    // 示例5：函数指针作为返回值
    {
        printf("\n=== Example 5: Function Pointer as Return Value ===\n");
        char op;
        printf("Enter an operator (+, -, *, /): ");
        scanf(" %c", &op);  // 注意前面的空格，跳过换行符

        MathOperation func = get_operation(op);
        if (func != NULL) {
            int result = func(6, 2);
            printf("6 %c 2 = %d\n", op, result);
        } else {
            printf("Invalid operator.\n");
        }
    }

    return 0;
}
