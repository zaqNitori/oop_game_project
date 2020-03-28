#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameObject.h"

namespace game_framework
{
    Man::Man(int x, int y, int start, int end, bool direction) : x(x), y(y), moving(true), direction(direction), velocity(3)
    {
        range[0] = start;
        range[1] = end;
        is_alive = true;
        is_focused = false;
    }

    void Man::OnMove()
    {
        if (moving)
        {
            if (direction)
            {
                if (x < range[1])
                    x += velocity;
                else
                    SetDirection(false);
            }
            else
            {
                if (x > range[0])
                    x -= velocity;
                else
                    SetDirection(true);
            }

            if (direction)
            {
                man_right.OnMove();
            }
            else
            {
                man_left.OnMove();
            }
        }
    }

    void Man::OnShow(CGameMap* map)
    {
        if (moving) //�O�_���b����
            if (direction) //false => ����, true => ���k
            {
                man_right.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
                man_right.OnShow();
            }
            else
            {
                man_left.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
                man_left.OnShow();
            }
        else
        {
            if (direction) //false => ����, true => ���k
            {
                man_right_stand.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
                man_right_stand.ShowBitmap();
            }
            else
            {
                man_left_stand.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
                man_left_stand.ShowBitmap();
            }
        }
    }


    void Man::SetDirection(bool direction)
    {
        this->direction = direction;
    }

    void Man::SetMoving(bool status)
    {
        moving = status;
    }

    bool Man::HitMainGirl(CGameMap* map, MainGirl* girl)
    {
        int cursor_x = girl->GetCursorX();
        int cursor_y = girl->GetCursorY();
        int x2 = x + man_left_stand.Width();
        int y2 = y + man_left_stand.Height();
        return (cursor_x >= map->ScreenX(x) && cursor_y >= map->ScreenY(y)
                && cursor_x <= map->ScreenX(x2) && cursor_y <= (map->ScreenY(y2) - man_left_stand.Height() / 2));
    }


    void Man::SetIsAlive(bool status)
    {
        is_alive = status;
    }

    bool Man::IsAlive()
    {
        return is_alive;
    }

    void Man::SetIsFocused(bool status)
    {
        is_focused = status;
    }

    bool Man::IsFocused()
    {
        return is_focused;
    }

    int Man::GetX()
    {
        return x;
    }

    int Man::GetY()
    {
        return y;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    NormalMan::NormalMan(int x, int y, int start, int end, bool direction, int type) : Man(x, y, start, end, direction), type(type)
    {
    }

    void NormalMan::LoadBitMap()
    {
        char text[100] = { 0 };
        strcpy(text, ("RES/normalMan" + to_string(type) + "/left/stand.bmp").c_str());
        man_left_stand.LoadBitmap(text, RGB(255, 255, 255));
        strcpy(text, ("RES/normalMan" + to_string(type) + "/right/stand.bmp").c_str());
        man_right_stand.LoadBitmap(text, RGB(255, 255, 255));

        for (int i = 1; i <= 5; i++)
        {
            strcpy(text, ("RES/normalMan" + to_string(type) + "/right/normalMan (" + to_string(i) + ").bmp").c_str());
            man_right.AddBitmap(text, RGB(255, 255, 255));
        }

        man_right.SetDelayCount(13);

        for (int i = 1; i <= 5; i++)
        {
            strcpy(text, ("RES/normalMan" + to_string(type) + "/left/normalMan (" + to_string(i) + ").bmp").c_str());
            man_left.AddBitmap(text, RGB(255, 255, 255));
        }

        man_left.SetDelayCount(13);
    }

}