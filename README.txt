//**********************************************************************//
//	TRABAJO PR�CTICO FINAL: Generador de m�quinas de estados	//
//**********************************************************************//

Grupo N� 2:
	Gabriel Cufaro
	Leandro Luo
	Bernardo Michel
	Agust�n De Ruschi

//////////////////////////////////////////////////////////////////////////
//			MANUAL DE USUARIO				//
//////////////////////////////////////////////////////////////////////////

	Cada vez que se clickea en un bot�n, se debe ingresar el nombre o 
  requisito que el programa necesita para terminar la acci�n. Por ejemplo,
  si se hace click en el bot�n "Agregar Estado", antes de que aparezca, 
  se pide ingresar el nombre, apreta enter y reci�n ah� aparece el estado.

	Para borrar un estado, hacer click en el estado que se desea
  borrar previo a apretar el bot�n "Eliminar Estado", esto borra el estado
  y las trancisiones que tiene como origen y destino.

	Para borrar una transici�n hay que apretar los estados vinculados
  a la misma e ingresar el evento asociado a ella.
		
	Para borrar una funci�n, pide el estado de origen, el de destino y
  el evento relacionado a la misma.

	Es EXTREMADAMENTE necesario que el usuario tenga las funciones que 
  ingresa en archivos separados con el mismo nombre que asigna a las 
  funciones en el programa.

	Una vez que el usuario esta conforme con la m�quina de estado que
  crea, debe apretar el bot�n "Generar Makefile", los archivos que genera
  el programa se encuentran en la carpeta "OUTPUT". En caso de que haya
  generado el makefile y no est� conforme, puede editar de nuevo la m�quina
  y volver a apretar el bot�n sin ningun tipo de inconveniente.
