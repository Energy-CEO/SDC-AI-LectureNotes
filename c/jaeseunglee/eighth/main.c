#include <stdio.h>

#include "player/entity/player.h"
#include "dice/entity/dice.h"
#include "utility/random.h"
#include "utility/common.h"

#define MAX_PLAYER          2
#define MAX_DICE            2

#define FIRST_DICE          0
#define SECOND_DICE         1

int find_target_dice(int current_index)
{
    return current_index ? 0 : 1;
}

//                          player *player_object[MAX_PLAYER];
void player_info_allocation(player **player_object_array, char **name)
{
    int i;

    for (i = 0; i < MAX_PLAYER; i++)
    {
        // init_player_object()에서 할당된 Heap Memory주소는
        // player_obejct_array[index]에 배치됨

        // 각각의 player_oject_array[index]에 가면 무엇이 있는가?
        // Heap에 저장된 메모리 => player 객체
        player_object_array[i] = init_player_object();


        // player 객체에 name값 설정
        set_player_name(player_object_array[i], name[i]);

        // player 객체의 toString() 메서드 <- Java 스타일
        // player 객체의 정보 출력 <- Java를 모를 경우

        // 무엇을 전달하는가?
        // 메모리 주소값 <-- 세부사항
        // player 객체 <-- 도메인
        // 결론적으로 도메인 관점은 아무리 복잡한 상황이더라도 직관성을 제공
        // 이름을 길고 목적성이 명확하게 쓰는 것은 협업효율이 올라감
        print_player_object(player_object_array[i]);
    }
}

void dice_memory_allocation(dice *dice_array[MAX_PLAYER][MAX_DICE])
{
    int i, j;

    random_seed_config();

    for (i = 0; i < MAX_PLAYER; i++)
    {
        for (j = 0; j < MAX_DICE; j++)
        {
            dice_array[i][j] = init_dice_object();
        }
    }
}

void apply_dice_skill(bool isFirstDiceIsEven, 
                    dice *dice_array[MAX_PLAYER][MAX_DICE], 
                    int player_index)
{
    if (isFirstDiceIsEven)
    {
        int target_index;
        int second_dice = get_dice_number(
            dice_array[player_index][SECOND_DICE]);

        switch (second_dice)
        {
            case 2:
                printf("2번 스킬: +3\n");
                add_score(dice_array[player_index][SECOND_DICE]);
                break;
            
            case 3:
                printf("3번 스킬: -4\n");
                target_index = find_target_dice(player_index);
                sub_score(dice_array[target_index][SECOND_DICE]);
                break;
            
            case 4:
                printf("뒤졌음: -4444\n");
                death(dice_array[player_index][SECOND_DICE]);
                break;
            
            default:
                break;
        }
    }
}

void play_dice_game(dice *dice_array[MAX_PLAYER][MAX_DICE])
{
    int i, j;

    for (i = 0; i < MAX_PLAYER; i++)
    {
        printf("player: %d\n", i);
        for (j = 0; j < MAX_DICE; j++)
        {
            bool isFirstDiceIsEven = false;
            if (j == SECOND_DICE)
            {
                // '!' 는 NOT 연산자로
                // 참을 부정하면 거짓
                // 거짓을 부정하면 참
                isFirstDiceIsEven = decision_even(
                        get_dice_number(dice_array[i][FIRST_DICE]));

                if (!isFirstDiceIsEven)
                {
                    break;
                }
            }

            roll_dice(dice_array[i][j]);
            print_dice_object(dice_array[i][j]);

            apply_dice_skill(isFirstDiceIsEven, dice_array, i);
        }
    }
}

int main (void)
{
    // int i, j;
    // player 객체를 관리하는 배열
    // Player playerArray[MAX_PLAYER]; <- Java
    // player는 무엇인가 ?
    // 우리가 커스텀한 데이터타입임
    // int와 int *의 차이점은 무엇인가 ?
    player *player_object[MAX_PLAYER];
    char *name[MAX_PLAYER] = {
        
        "낵아마",
        "낵아뭐"
    };

    dice *dice_array[MAX_PLAYER][MAX_DICE];

    printf("Eighth work\n");

    player_info_allocation(player_object, name);
    /*
    for (i = 0; i < MAX_PLAYER; i++)
    {
        player_object[i] = init_player_object();
        set_player_name(player_object[i], name[i]);
        print_player_object(player_object[i]);
    }
    */

    dice_memory_allocation(dice_array);
    /*
    random_seed_config();

    for (i = 0; i < MAX_PLAYER; i++)
    {
        for (j = 0; j < MAX_DICE; j++)
        {
            dice_array[i][j] = init_dice_object();
        }
    }
    */

    play_dice_game(dice_array);

   /*
    for (i = 0; i < MAX_PLAYER; i++)
    {
        printf("player: %d\n", i);
        for (j = 0; j < MAX_DICE; j++)
        {
            bool isFirstDiceIsEven = false;
            if (j == SECOND_DICE)
            {
                // '!' 는 NOT 연산자로
                // 참을 부정하면 거짓
                // 거짓을 부정하면 참
                isFirstDiceIsEven = decision_even(
                        get_dice_number(dice_array[i][FIRST_DICE]));

                if (!isFirstDiceIsEven)
                {
                    break;
                }
            }

            roll_dice(dice_array[i][j]);
            print_dice_object(dice_array[i][j]);

            apply_dice_skill(isFirstDiceIsEven, dice_array, i);

            if (isFirstDiceIsEven)
            {
                int target_index;
                int second_dice = get_dice_number(
                    dice_array[i][SECOND_DICE]);

                switch (second_dice)
                {
                    case 2:
                        printf("2번 스킬: +3\n");
                        add_score(dice_array[i][SECOND_DICE]);
                        break;
                    
                    case 3:
                        printf("3번 스킬: -4\n");
                        target_index = find_target_dice(i);
                        sub_score(dice_array[target_index][SECOND_DICE]);
                        break;
                    
                    case 4:
                        printf("뒤졌음: -4444\n");
                        death(dice_array[i][SECOND_DICE]);
                        break;
                    
                    default:
                        break;
                }
            }
        }
    }
    */
    
    return 0;
}