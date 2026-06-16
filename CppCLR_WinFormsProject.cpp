#include "pch.h"

// Must include ALL headers for full type definitions (needed by forward declarations)
#include "Models/Usuario.h"
#include "Models/Cliente.h"
#include "Models/Producto.h"
#include "Models/Factura.h"
#include "Models/DetalleFactura.h"
#include "Servicios/Conexion.h"
#include "Servicios/Autenticacion.h"
#include "Vistas/VentanaPrincipal.h"
#include "Vistas/VistaLogin.h"
#include "Vistas/VistaRegistro.h"
#include "Vistas/VistaAdmin.h"
#include "Vistas/VistaCajero.h"
#include "Vistas/VistaFactura.h"
#include "Vistas/VistaDetallesFactura.h"
#include "Vistas/VistaClienteABM.h"
#include "Vistas/VistaUsuarioABM.h"
#include "Vistas/VistaDepositoABM.h"
#include "Vistas/VistaFormulario.h"
#include "Controladores/ControladorLogin.h"
#include "Controladores/ControladorRegistro.h"
#include "Controladores/ControladorAdmin.h"
#include "Controladores/ControladorCajero.h"
#include "Controladores/ControladorFactura.h"
#include "Controladores/ControladorClienteABM.h"
#include "Controladores/ControladorUsuarioABM.h"
#include "Controladores/ControladorDepositoABM.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Vistas;
using namespace Controladores;

// Method implementations that gcnew other controladores (requires all types defined)
#include "Controladores/ControladoresImpl.h"

[STAThread]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    auto ventana = gcnew VentanaPrincipal();
    gcnew ControladorLogin(ventana);
    Application::Run(ventana);
    return 0;
}
