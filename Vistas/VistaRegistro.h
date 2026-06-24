#pragma once
#include "..\Filtros\FiltroNumerico.h"
#include "..\Filtros\FiltroTexto.h"
#include "..\Filtros\FiltroAlfanumerico.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Filtros;

namespace Vistas {
    public ref class VistaRegistro {
    public:
        Panel^ panelRegistro;
        TextBox^ nombreTF;
        TextBox^ apellidoTF;
        TextBox^ dniTF;
        TextBox^ telefonoTF;
        TextBox^ direccionTF;
        TextBox^ mailTF;
        TextBox^ password;
        Button^ registrarse;
        Button^ botonVolver;

        VistaRegistro() {
            auto azul = Color::LightSkyBlue;

            panelRegistro = gcnew Panel();
            panelRegistro->Size = System::Drawing::Size(800, 600);

            int lblX = 250;
            int tbX = 350;
            int tbW = 200;
            int yStart = 60;
            int rowH = 35;

            array<String^>^ labels = { L"Nombre:", L"Apellido:", L"DNI:", L"Telefono:", L"Direccion:", L"Mail:", L"Password:" };
            array<TextBox^>^ textBoxes = gcnew array<TextBox^>(7);

            for (int i = 0; i < 7; i++) {
                auto lbl = gcnew Label();
                lbl->Text = labels[i];
                lbl->Location = Point(lblX, yStart + i * rowH);
                lbl->Size = System::Drawing::Size(90, 25);
                lbl->TextAlign = ContentAlignment::MiddleLeft;
                panelRegistro->Controls->Add(lbl);

                textBoxes[i] = gcnew TextBox();
                textBoxes[i]->Location = Point(tbX, yStart + i * rowH);
                textBoxes[i]->Size = System::Drawing::Size(tbW, 25);
                panelRegistro->Controls->Add(textBoxes[i]);
            }

            nombreTF = textBoxes[0];
            apellidoTF = textBoxes[1];
            dniTF = textBoxes[2];
            telefonoTF = textBoxes[3];
            direccionTF = textBoxes[4];
            mailTF = textBoxes[5];
            password = textBoxes[6];
            password->UseSystemPasswordChar = true;

            FiltroTexto::Aplicar(nombreTF);
            FiltroTexto::Aplicar(apellidoTF);
            FiltroNumerico::Aplicar(dniTF);
            FiltroNumerico::Aplicar(telefonoTF);
            FiltroAlfanumerico::Aplicar(direccionTF);
            FiltroAlfanumerico::Aplicar(mailTF);

            registrarse = gcnew Button();
            registrarse->Text = L"Crear Usuario";
            registrarse->Location = Point(lblX, yStart + 7 * rowH + 5);
            registrarse->Size = System::Drawing::Size(140, 35);
            registrarse->BackColor = azul;
            panelRegistro->Controls->Add(registrarse);

            botonVolver = gcnew Button();
            botonVolver->Text = L"Volver";
            botonVolver->Location = Point(lblX + 155, yStart + 7 * rowH + 5);
            botonVolver->Size = System::Drawing::Size(140, 35);
            botonVolver->BackColor = Color::Gainsboro;
            panelRegistro->Controls->Add(botonVolver);
        }
    };
}
