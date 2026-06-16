#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

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
            panelRegistro = gcnew Panel();
            panelRegistro->Size = System::Drawing::Size(800, 600);

            array<String^>^ labels = { L"Nombre:", L"Apellido:", L"DNI:", L"Telefono:", L"Direccion:", L"Mail:", L"Password:" };
            array<TextBox^>^ textBoxes = gcnew array<TextBox^>(7);

            int y = 150;
            for (int i = 0; i < 7; i++) {
                auto lbl = gcnew Label();
                lbl->Text = labels[i];
                lbl->Location = Point(280, y);
                lbl->Size = System::Drawing::Size(80, 20);
                panelRegistro->Controls->Add(lbl);

                textBoxes[i] = gcnew TextBox();
                textBoxes[i]->Location = Point(370, y);
                textBoxes[i]->Size = System::Drawing::Size(150, 20);
                panelRegistro->Controls->Add(textBoxes[i]);
                y += 30;
            }

            nombreTF = textBoxes[0];
            apellidoTF = textBoxes[1];
            dniTF = textBoxes[2];
            telefonoTF = textBoxes[3];
            direccionTF = textBoxes[4];
            mailTF = textBoxes[5];
            password = textBoxes[6];
            password->UseSystemPasswordChar = true;

            registrarse = gcnew Button();
            registrarse->Text = L"Registrarse";
            registrarse->Location = Point(280, y + 10);
            registrarse->Size = System::Drawing::Size(110, 30);
            panelRegistro->Controls->Add(registrarse);

            botonVolver = gcnew Button();
            botonVolver->Text = L"Volver";
            botonVolver->Location = Point(410, y + 10);
            botonVolver->Size = System::Drawing::Size(110, 30);
            panelRegistro->Controls->Add(botonVolver);
        }
    };
}
