
# COMMAND="comando"
# Guardar string en una "variable"

# $COMMAND 
# Ejecutar comando guardado en la variable

# echo $COMMAND
#Mostrar comando por pantalla

# $COMMAND | $TIEMPOS >> $OUTPUT
#Ejecutar $TIEMPOS pasandole como cin el cout de $COMMAND y lo guarda en $OUTPUTs


OUTPUT_EXTERN_PATH="/media/libre/algo32c2014"

STEP=10
MUESTRAS=10
TIEMPOS="./../../ej1 -t -g 1 -m "$MUESTRAS

#Lote: Variacion en la cantidad de nodos, probabilidad de arista y particiones
for k in 1 2 3 4 5
do
	for d in 0.20 0.5 0.80
	do
		for i in {1..20}
		do	
			INSTANCE=$(($STEP * $i))
			#echo $INSTANCE$
				
			INPUT="-a random -n "$INSTANCE$" -d "$d$" -k "$k
			COMMAND="python ./../../resources/genInput.py "$INPUT 
			#echo "INPUT: "$COMMAND
				
			OUTPUT=$OUTPUT_EXTERN_PATH"/greedy_time/ej3_metrics_greedy_time_k:"$k$"_d:"$d
			#echo "OUTPUT: "$OUTPUT
				
			$COMMAND | $TIEMPOS >> $OUTPUT
			echo "FULL: "$COMMAND$" | "$TIEMPOS		
		done
	done
done
