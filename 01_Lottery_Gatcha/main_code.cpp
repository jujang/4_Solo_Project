#include<iostream>
#include<random>
#include<algorithm>
#include<windows.h>

using namespace std;


class Random {
public:
    unsigned int class_number;
    unsigned int six_number[6];
};

void Lotto(int game_number, Random* number_set) {

    //난수 생성
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 45);  // 6자리 숫자에 대한 난수 생성 범위 지정(균등 분포방식)

    for (int i = 0; i < game_number; i++) {
        for (int j = 0; j < 6; j++) {
            number_set[i].six_number[j] = dis(gen);
            //여기까지가 기본 랜덤값 받기

            //중복된 값이 있는 경우, 랜덤값 다시 받기(중복 안 될때까지 다시...)
            int retry = 1;      //중복숫자시, 숫자생성 반복
            int retry_flag = 0; //반복 보조 flag <- 얘가 1이면 중복 숫자가 있으니 다시 숫자를 받고 처음부터 다시 체크하기, 그후 중복 숫자가 없게되면 0으로 clear
            while (retry == 1) {
                for (int x = j - 1; x >= 0; x--) {
                    if (number_set[i].six_number[j] == number_set[i].six_number[x]) {
                        number_set[i].six_number[j] = dis(gen);
                        retry_flag = 1; // 반복 보조 flag set, 이럼 반복을 해야됨
                    }
                }
                if (retry_flag != 1) retry = 0; //탐색중에 중복 숫자가 없다면 반복 중지
                retry_flag = 0; //반복 보조 flag clear
            }
        }

        //랜덤생성된 숫자를 정렬하는 함수
        sort(number_set[i].six_number, number_set[i].six_number + 6);

        //잠시 쉬는 코드
        Sleep(250);
        cout << ".";
    }
}

void Pension_Lottery(int game_number, Random* number_set) {

    //난수 생성기
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis_1(1, 5);  //얘는 '조'에 대해서 난수 생성 (균등 분포)
    uniform_int_distribution<int> dis_2(0, 9);  //얘는 뒷 6자리 숫자에 대해서 난수 생성 (난수 분포)

    for (int i = 0; i < game_number; i++) {
        number_set[i].class_number = dis_1(gen);
        for (int j = 0; j < 6; j++) {
            number_set[i].six_number[j] = dis_2(gen);
        }

        //잠시 쉬는 코드
        Sleep(300);
        cout << ".";
    }
}

//이건 만약에 다른 타입의 입력이 들어가서 에러가 생겼을 경우에 에러지워주고, 버퍼도 지워주는 함수임
//입력을 받을 때마다 이것을 넣어두었음
void buffer_ok(void) {
    if (cin.fail()) {
        cin.clear();
    }
    cin.ignore(INT_MAX, '\n');
}

int main(void) {

    //종료 기능
    char exit = 'n';

    while (exit == 'n' || exit == 'N') {

        //사용 기능 선택 (로또 or 연금복권)
        int mode; // 1: 로또, 2: 연금복권
        cout << "어서 오십시오" << endl;
        cout << "복권 숫자('가능성의 숫자') 자동 선별 프로그램입니다" << endl;
        cout << "1. 로또" << endl << "2. 연금복권" << endl;
        cout << "어떤 모드를 사용하시겠습니까?(숫자로 입력해주세요): ";
        cin >> mode;
        buffer_ok();
        while (mode != 1 && mode != 2) {
            cout << "잘못 입력하였습니다. 다시 입력해주세요: ";
            cin >> mode;
            buffer_ok();
        }
        if (mode == 1) {
            cout << endl << "로또 모드를 선택해주셨습니다" << endl;
        }
        else {
            cout << endl << "연금복권 모드를 선택해주셨습니다" << endl;
        }


        //희망 게임수 선택 (1~10)
        int game_number;
        cout << "선별 희망 게임수를 작성해주세요(1~10 이내): ";
        cin >> game_number;
        buffer_ok();
        while (game_number < 1 || game_number > 10) {
            cout << "잘못 입력하였습니다. 다시 입력해주세요: ";
            cin >> game_number;
            buffer_ok();
        }
        Random* winning_number = new Random[game_number]; //번호가 들어갈 세트 선언


        //번호 선별
        cout << endl << "선별할 번호 세트수 : " << game_number << endl;
        cout << "가능성의 번호 선별을 시작하겠습니다" << endl;
        cout << "선별중";
        if (mode == 1) {
            Lotto(game_number, winning_number);
        }
        else {
            Pension_Lottery(game_number, winning_number);
        }
        cout << endl << "가능성의 번호 선별이 완료되었습니다" << endl << endl;


        cout << "선별된 번호 세트는 다음과 같습니다" << endl;
        //번호 발표
        for (int i = 0; i < game_number; i++) {
            if (mode == 2) {
                cout << winning_number[i].class_number << "조  ";
            }
            for (int j = 0; j < 6; j++) {
                cout << winning_number[i].six_number[j] << " ";
            }
            cout << endl;
        }
        cout << "이상으로 이번 선별을 마치겠습니다" << endl << endl;
        cout << "프로그램을 종료하시겠습니까?" << endl;
        cout << "(종료를 희망하실 경우 'Y'를, 추가 수행을 희망하실 경우 'N'을 눌러주세요) : ";
        //이거 나중에 y와 n으로 바꿉시당
        cin >> exit;
        buffer_ok();
        while (exit != 'Y' && exit != 'y' && exit != 'N' && exit != 'n') {
            cout << "잘 못 입력하였습니다. 다시 입력해주세요 : ";
            cin >> exit;
            buffer_ok();
        }

        //재시작 or 종료
        if (exit == 'Y' || exit == 'y') {
            cout << endl << "프로그램을 종료하겠습니다" << endl;
            cout << endl << "로또 생성 프로그램 ver1.1" << endl;
            cout << "programmed by 장정욱" << " at 2021/08/28" << endl;
        }
        else {
            cout << endl << endl << endl;
        }
    }


    return 0;
}

//필요한 것

//모드 :  1)로또, 2)연금복권
//방식1 : 1)로또
//        구매희망 갯수 선택 -> 그만큼 출력
//        초기로? or 종료?
//방식2 : 2)연금복권
//        구매희망 갯수 선택 -> 그만큼 출력
//        초기로? or 종료?

//구현한 것
//@1. 값 입력 받을 때에 만약에 스페이스 바가 있다면 그건 다음번 입력에서 쓰이는데 그러면 내가 원하는 값이 아닌 이전의 값을 가져올 수가 있음...
//   다음으로 넘어가게 된다면 이전에 입력된 값들은 지워버리고 싶음... 그런 기능이 뭔지 알아봐야겟음...
//@1_2. 에러비트 이슈(숫자 입력받아야 하는 상황에서 문자를 입력받으면 똑같은 출력이 무한 반복되는 경우) 초기화 해결
//@2. 문자 인식방법
//@3. 난수 생성방법
//@3_1. 난수 생성시 중복값 방지 코드 생성(로또 모드일 경우)
//@3_2. 랜덤 생성값 정렬하기-sort 함수 사용하기(로또 모드일 경우)
//@4. 잠시 쉬는 코드 -> 'Sleep()'함수 사용 (#include<windows.h> 필요)
//@5. 하나의 프로그램, 즉 아이콘화된 프로그램으로 만들기 -> 실행 프로그램(exe확장자 파일) 추출방법(및 전송방법) 알아냄

//패치노트
//1.0 : 기본 프로그램 구현 완료 at 21/08/28
//1.1 : 중복숫자 탐색 알고리즘 오류 해결 at 21/08/29 -> 'retry'변수 외에도 'retry_flag'변수 사용으로 해결