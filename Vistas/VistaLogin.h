#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

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
            panelLogin = gcnew Panel();
            panelLogin->Size = System::Drawing::Size(800, 600);

            auto lblMail = gcnew Label();
            lblMail->Text = L"Mail:";
            lblMail->Location = Point(300, 200);
            lblMail->Size = System::Drawing::Size(80, 20);
            panelLogin->Controls->Add(lblMail);

            mailTextField = gcnew TextBox();
            mailTextField->Location = Point(380, 200);
            mailTextField->Size = System::Drawing::Size(150, 20);
            panelLogin->Controls->Add(mailTextField);

            auto lblPassword = gcnew Label();
            lblPassword->Text = L"Password:";
            lblPassword->Location = Point(300, 230);
            lblPassword->Size = System::Drawing::Size(80, 20);
            panelLogin->Controls->Add(lblPassword);

            passwordTextField = gcnew TextBox();
            passwordTextField->Location = Point(380, 230);
            passwordTextField->Size = System::Drawing::Size(150, 20);
            passwordTextField->UseSystemPasswordChar = true;
            panelLogin->Controls->Add(passwordTextField);

            chkMostrarPassword = gcnew CheckBox();
            chkMostrarPassword->Text = L"Mostrar contrasena";
            chkMostrarPassword->Location = Point(380, 253);
            chkMostrarPassword->Size = System::Drawing::Size(130, 17);
            chkMostrarPassword->CheckedChanged += gcnew EventHandler(this, &VistaLogin::MostrarPasswordChanged);
            panelLogin->Controls->Add(chkMostrarPassword);

            botonLogin = gcnew Button();
            botonLogin->Text = L"Iniciar sesion";
            botonLogin->Location = Point(300, 270);
            botonLogin->Size = System::Drawing::Size(100, 30);
            panelLogin->Controls->Add(botonLogin);

            botonRegistrar = gcnew Button();
            botonRegistrar->Text = L"Registrarse";
            botonRegistrar->Location = Point(430, 270);
            botonRegistrar->Size = System::Drawing::Size(100, 30);
            panelLogin->Controls->Add(botonRegistrar);
        }

        void MostrarPasswordChanged(Object^ sender, EventArgs^ e) {
            passwordTextField->UseSystemPasswordChar = !chkMostrarPassword->Checked;
        }
    };
}
