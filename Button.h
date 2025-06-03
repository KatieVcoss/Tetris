#pragma once  // ������ �� �������������� ��������� ������������� �����

#include <SFML/Graphics.hpp>  
#include <iostream>           

// ����� ������ � ����� ����������� (���������� � �������)
class Button {
public:
    // ����������� ������, ��� 
    //   location - ������� ������ �� ������;
    //   normal - �������� ��� ����������� ���������;
    //   clicked - �������� ��� �������� ���������;
    Button(sf::Vector2f location, const sf::Texture& normal, const sf::Texture& clicked);

    // �������� ����� �� ������,���
    //   mousePos - ���������� ������� ���� (�� ��������� (-1,-1))
    bool checkClick(sf::Vector2i mousePos = sf::Vector2i(-1, -1));

    // ��������� ������� ��� ���������
    sf::Sprite* getSprite();

private:
    // ����������� ������������� ������:
    sf::Sprite normal;    // ������ ����������� ���������
    sf::Sprite clicked;   // ������ �������� ���������

    // ��������� �� ������� ������ (��� ���������)
    sf::Sprite* currentSpr;

    // ������� ��������� ������:
    //   false - �� ������
    //   true - ������
    bool current = false;

    // ��������� ��������� ������ - state - ����� ��������� ������
    void setState(bool state);
};