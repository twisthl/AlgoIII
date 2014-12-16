
# COMMAND="comando"
# Guardar string en una "variable"

# $COMMAND 
# Ejecutar comando guardado en la variable

# echo $COMMAND
#Mostrar comando por pantalla

# $COMMAND | $TIEMPOS >> $OUTPUT
#Ejecutar $TIEMPOS pasandole como cin el cout de $COMMAND y lo guarda en $OUTPUTs


STEP=1
MUESTRAS=1
TIEMPOS="./../../tp3 -t -b -m "$MUESTRAS

#Lote: Variacion en la cantidad de nodos, probabilidad de arista y particiones
for k in 1 2 3 4 5
do
	for d in 0.20 0.5 0.80
	do
		for i in {5..16}
		do	
			INSTANCE=$(($STEP * $i))
			#echo $INSTANCE$
				
			INPUT="-a random -n "$INSTANCE$" -d "$d$" -k "$k
			COMMAND="python ./../../resources/genInput.py "$INPUT 
			#echo "INPUT: "$COMMAND
				
			OUTPUT="backtrack_times/ej2_metrics_backtrack_time_k:"$k$"_d:"$d
			#echo "OUTPUT: "$OUTPUT
				
			$COMMAND | $TIEMPOS >> $OUTPUT
			echo "FULL: "$COMMAND$" | "$TIEMPOS		
		done
	done
done

