#!/usr/bin/env bash

mkdir -p resultados
mkdir -p diffs

for i in $(seq 1 100); do
    num=$(printf "%04d" "$i")

    echo "Executando simulador $num..."
    ./simulador "$i"

    gabarito="saidas/saida-${num}.txt"
    gerado="resultados/resultado-${num}.txt"
    arq_diff="diffs/diff-${num}.txt"

    if [[ -f "$gabarito" && -f "$gerado" ]]; then
        diff -u "$gabarito" "$gerado" > "$arq_diff"
        if [[ ! -s "$arq_diff" ]]; then
            rm "$arq_diff"
            echo "OK: Sem diferenças para ${num}"
        else
            echo "ALERTA: Diferenças encontradas → $arq_diff"
        fi
    else
        echo "ERRO: Arquivo ausente para ${num}"
    fi
done

echo "Processamento concluído."