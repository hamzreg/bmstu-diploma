WORK := thesis

default:
	pdflatex $(WORK).tex
	biber $(WORK)
	pdflatex $(WORK).tex
	pdflatex $(WORK).tex

clean:
	rm -rf *.aux *.bbl *.bcf *.blg *.log *.out *.run.xml *.toc
