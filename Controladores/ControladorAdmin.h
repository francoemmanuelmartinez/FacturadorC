#pragma once
#include "..\Models\Usuario.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaAdmin.h"

namespace Controladores {
    ref class ControladorLogin;
    ref class ControladorCajero;
    ref class ControladorClienteABM;
    ref class ControladorUsuarioABM;
    ref class ControladorDepositoABM;
}

using namespace Models;
using namespace Vistas;

namespace Controladores {
    public ref class ControladorAdmin {
    private:
        Usuario^ usuario;
        VentanaPrincipal^ ventanaPrincipal;

        void botonUsuarios_Click(Object^ sender, EventArgs^ e);
        void botonClientes_Click(Object^ sender, EventArgs^ e);
        void botonFacturar_Click(Object^ sender, EventArgs^ e);
        void botonDeposito_Click(Object^ sender, EventArgs^ e);
        void cerrarSesion_Click(Object^ sender, EventArgs^ e);

    public:
        ControladorAdmin() {}

        ControladorAdmin(Usuario^ usuario, VentanaPrincipal^ ventanaPrincipal) {
            this->usuario = usuario;
            this->ventanaPrincipal = ventanaPrincipal;
            auto vistaAdmin = gcnew VistaAdmin();
            ventanaPrincipal->setVista(vistaAdmin->panelAdmin);

            vistaAdmin->botonAdministrarUsuarios->Click += gcnew EventHandler(this, &ControladorAdmin::botonUsuarios_Click);
            vistaAdmin->botonAdministrarClientes->Click += gcnew EventHandler(this, &ControladorAdmin::botonClientes_Click);
            vistaAdmin->botonFacturar->Click += gcnew EventHandler(this, &ControladorAdmin::botonFacturar_Click);
            vistaAdmin->botonAdministrarDeposito->Click += gcnew EventHandler(this, &ControladorAdmin::botonDeposito_Click);
            vistaAdmin->cerrarSesion->Click += gcnew EventHandler(this, &ControladorAdmin::cerrarSesion_Click);
        }
    };
}
