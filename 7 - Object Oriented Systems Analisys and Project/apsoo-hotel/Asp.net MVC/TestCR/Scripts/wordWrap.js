function wordWrap() {
    /******
    * wordWrap - Efetua quebra em palavras que não cabem na largura
    *            de seu elemento pai (até que chegue o CSS3)
    * Use a vontade mas coloque meu nome nos créditos. Tenha ética.
    * Dúvidas, me mande um email.
    * Versão: 1.0 - 26/04/2006
    * Autor: Micox - Náiron José C. Guimarães - micoxjcg@yahoo.com.br
    * Uso: chame a função no onload do body.
    *      coloque a classe "word-wrap" nos parágrafos que quiser a quebra
    *******/
    var larg_total, larg_carac, quant_quebra, pos_quebra;
    var elementos, quem, caracs, texto, display_orig;

    elementos = document.getElementsByTagName("p")

    for (var i = 0; i < elementos.length; i++) {
        if (elementos[i].className == "word-wrap") {
            quem = elementos[i];

            quem.innerHTML = String(quem.innerHTML).replace(/ /g, "Ø")
            texto = String(quem.innerHTML)

            quem.innerHTML = " "

            display_orig = quem.style.display;
            quem.style.display = "block";
            larg_oficial = quem.offsetWidth;
            //alert("oficial: " + larg_oficial)
            //alert("display " + quem.style.display)
            if (!document.all) quem.style.display = "table";
            //alert("display " + quem.style.display)
            quem.innerHTML = texto;
            larg_total = quem.offsetWidth;
            //alert("total: " + larg_total)

            pos_quebra = 0;
            caracs = texto.length;
            texto = texto.replace(/Ø/g, " ")
            larg_carac = larg_total / caracs
            if (larg_total > larg_oficial) {
                quant_quebra = parseInt(larg_oficial / larg_carac)
                quant_quebra = quant_quebra - (parseInt(quant_quebra / 6)) //quanto menor o num, maior a garantia;
                quem.innerHTML = ""
                while (pos_quebra <= caracs) {
                    quem.innerHTML = quem.innerHTML + texto.substring(pos_quebra, pos_quebra + quant_quebra) + " "
                    pos_quebra = pos_quebra + quant_quebra;
                }
            } else {
                quem.innerHTML = texto;
            } //end if do larg_total>larg_oficial
            quem.style.display = display_orig;
        } //end if do word wrap
    } //end for loop dos elementos
}