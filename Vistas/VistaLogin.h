#pragma once
#include "..\Filtros\FiltroAlfanumerico.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Filtros;

namespace Vistas {
    public ref class VistaLogin {
    public:
        Panel^ panelLogin;
        TextBox^ mailTextField;
        TextBox^ passwordTextField;
        Button^ botonLogin;
        Button^ botonRegistrar;
        CheckBox^ chkMostrarPassword;

        VistaLogin() {
            auto azul = Color::LightSkyBlue;

            panelLogin = gcnew Panel();
            panelLogin->Size = System::Drawing::Size(800, 600);

            auto lblBienvenido = gcnew Label();
            lblBienvenido->Text = L"Bienvenido";
            lblBienvenido->Font = gcnew System::Drawing::Font(L"Arial", 18, FontStyle::Bold);
            lblBienvenido->Location = Point(310, 130);
            lblBienvenido->Size = System::Drawing::Size(180, 40);
            lblBienvenido->TextAlign = ContentAlignment::MiddleCenter;
            panelLogin->Controls->Add(lblBienvenido);

            auto lblSub = gcnew Label();
            lblSub->Text = L"Inicie Sesion o Registrese";
            lblSub->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Regular);
            lblSub->Location = Point(270, 170);
            lblSub->Size = System::Drawing::Size(260, 25);
            lblSub->TextAlign = ContentAlignment::MiddleCenter;
            panelLogin->Controls->Add(lblSub);

            auto lblMail = gcnew Label();
            lblMail->Text = L"Mail:";
            lblMail->Location = Point(280, 220);
            lblMail->Size = System::Drawing::Size(80, 20);
            panelLogin->Controls->Add(lblMail);

            mailTextField = gcnew TextBox();
            mailTextField->Location = Point(360, 220);
            mailTextField->Size = System::Drawing::Size(160, 20);
            panelLogin->Controls->Add(mailTextField);
            FiltroAlfanumerico::Aplicar(mailTextField);

            auto lblPassword = gcnew Label();
            lblPassword->Text = L"Password:";
            lblPassword->Location = Point(280, 255);
            lblPassword->Size = System::Drawing::Size(80, 20);
            panelLogin->Controls->Add(lblPassword);

            passwordTextField = gcnew TextBox();
            passwordTextField->Location = Point(360, 255);
            passwordTextField->Size = System::Drawing::Size(160, 20);
            passwordTextField->UseSystemPasswordChar = true;
            panelLogin->Controls->Add(passwordTextField);

            chkMostrarPassword = gcnew CheckBox();
            chkMostrarPassword->Text = L"Mostrar contrasena";
            chkMostrarPassword->Location = Point(360, 280);
            chkMostrarPassword->Size = System::Drawing::Size(150, 17);
            chkMostrarPassword->CheckedChanged += gcnew EventHandler(this, &VistaLogin::MostrarPasswordChanged);
            panelLogin->Controls->Add(chkMostrarPassword);

            botonLogin = gcnew Button();
            botonLogin->Text = L"Iniciar Sesion";
            botonLogin->Location = Point(280, 310);
            botonLogin->Size = System::Drawing::Size(110, 30);
            botonLogin->BackColor = azul;
            panelLogin->Controls->Add(botonLogin);

            botonRegistrar = gcnew Button();
            botonRegistrar->Text = L"Crear Cuenta";
            botonRegistrar->Location = Point(410, 310);
            botonRegistrar->Size = System::Drawing::Size(110, 30);
            botonRegistrar->BackColor = azul;
            panelLogin->Controls->Add(botonRegistrar);
        }

        void MostrarPasswordChanged(Object^ sender, EventArgs^ e) {
            passwordTextField->UseSystemPasswordChar = !chkMostrarPassword->Checked;
        }
    };
}
