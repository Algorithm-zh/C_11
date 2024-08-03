#include <iostream>
#include <functional>
using namespace std;

void output(int x, int y)
{
    cout << x << " " << y << endl;
}

int main2(void)
{
    // ʹ�ð����󶨿ɵ��ö���Ͳ���, �����õõ��ķº���
    bind(output, 1, 2)();
    bind(output, placeholders::_1, 2)(10);
    bind(output, 2, placeholders::_1)(10);

    // error, ����ʱû�еڶ�������
    // bind(output, 2, placeholders::_2)(10);
    // ����ʱ��һ������10���̵��ˣ�û�б�ʹ��
    bind(output, 2, placeholders::_2)(10, 20);

    bind(output, placeholders::_1, placeholders::_2)(10, 20);
    bind(output, placeholders::_2, placeholders::_1)(10, 20);


    return 0;
}
