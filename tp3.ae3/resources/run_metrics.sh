
# COMMAND="comando"
# Guardar string en una "variable"

# $COMMAND 
# Ejecutar comando guardado en la variable

# echo $COMMAND
#Mostrar comando por pantalla

# $COMMAND | $TIEMPOS >> $OUTPUT
#Ejecutar $TIEMPOS pasandole como cin el cout de $COMMAND y lo guarda en $OUTPUTs


OUTPUT_EXTERN_PATH="/media/libre/algo32c2014"

STEP=100
TIEMPOS="./tiempos"
KNIGHTS=20

#Lote 1: Variacion en el tamaño del tablero con k fijo.
for i in {1..30}
	do	
		INSTANCE=$(($STEP * $i))
		#echo $INSTANCE$
		
		INPUT="-a random -n "$INSTANCE$" -k "$KNIGHTS
		COMMAND="python ./genInput.py "$INPUT 
		echo $COMMAND
		
		OUTPUT=$OUTPUT_EXTERN_PATH"/caballos_salvajes_experimento1.txt"
		echo $OUTPUT
		
		$COMMAND | $TIEMPOS >> $OUTPUT
		echo -e "Caballos salvajes experimento 1 terminado... \n"
	done
