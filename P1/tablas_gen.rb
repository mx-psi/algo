# Genera las tablas que reúnen los tiempos de ejecución de cada algoritmo para todos los ejecutores
# Uso: ruby tablas_gen.rb
# Salida: [nombredelprograma]_tabla.txt para cada programa

programas = ["burbuja", "fibonacci", "floyd", "hanoi", "heapsort", "insercion", "mergesort", "quicksort", "seleccion"]
nombres = ["antonio", "dario", "inaki", "jose_manuel", "pablo"]

def parsef(f)
   return f.sub(".", ",")
end

programas.each do |p|
   output = "\\begin{tabular}{|l|l|l|l|l|l|}\n\t\\hline\n" \
            "\tTamaño & Antonio & Darío & Iñaki & José Manuel & Pablo \\\\\n\t\\hline\n\t\\hline\n"
   data = []
   nombres.each do |n|
      filename = "dats/" + p + "_" + n + ".dat"
      subdata = File.read(filename).split("\n")
      for s in 0..subdata.length-1 do
         if n == nombres[0]
            data[s] = [subdata[s].split(" ")[0]]
         end
         data[s] << parsef(subdata[s].split(" ")[1])
      end
   end
   data.each do |d|
      output += "\t" + d.join(" & ") + " \\\\\n\t\\hline\n"
   end
   output += "\\end{tabular}\n"
   File.write("tablas/#{p}_tabla.tex", output)
end
