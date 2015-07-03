//**********************************************************************//
//	TRABAJO PRÁCTICO FINAL: Generador de máquinas de estados	//
//**********************************************************************//

Grupo Nº 2:
	Gabriel Cufaro
	Leandro Luo
	Bernardo Michel
	Agustín De Ruschi

//////////////////////////////////////////////////////////////////////////
//			MANUAL DE USUARIO				//
//////////////////////////////////////////////////////////////////////////

	Cada vez que se clickea en un botón, se debe ingresar el nombre o 
  requisito que el programa necesita para terminar la acción. Por ejemplo,
  si se hace click en el botón "Agregar Estado", antes de que aparezca, 
  se pide ingresar el nombre, apreta enter y recién ahí aparece el estado.

	Para borrar un estado, hacer click en el estado que se desea
  borrar previo a apretar el botón "Eliminar Estado", esto borra el estado
  y las trancisiones que tiene como origen y destino.

	Para borrar una transición hay que apretar los estados vinculados
  a la misma e ingresar el evento asociado a ella.
		
	Para borrar una función, pide el estado de origen, el de destino y
  el evento relacionado a la misma.

	Es EXTREMADAMENTE necesario que el usuario tenga las funciones que 
  ingresa en archivos separados con el mismo nombre que asigna a las 
  funciones en el programa.

	Una vez que el usuario esta conforme con la máquina de estado que
  crea, debe apretar el botón "Generar Makefile", los archivos que genera
  el programa se encuentran en la carpeta "OUTPUT". En caso de que haya
  generado el makefile y no esté conforme, puede editar de nuevo la máquina
  y volver a apretar el botón sin ningun tipo de inconveniente.
