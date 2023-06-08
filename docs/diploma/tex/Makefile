WORK := thesis

default:
	pdflatex -shell-escape $(WORK).tex
	biber $(WORK)
	pdflatex -shell-escape $(WORK).tex
	pdflatex -shell-escape $(WORK).tex

clean:
	rm -rf *.aux *.bbl *.bcf *.blg *.log *.out *.run.xml *.toc
