import os
import re

def clean_filename(filename):
    # Remove números do início até encontrar um caractere não numérico
    cleaned_name = re.sub(r'^\d+', '', filename)
    # Remove a extensão do arquivo
    cleaned_name = re.sub(r'\.[^.]+$', '', cleaned_name)
    return cleaned_name

def initalize_doc() -> str:
    return '''\\documentclass[a4paper,12pt]{article}
\\usepackage[utf8]{inputenc}
\\usepackage[brazil]{babel}
\\usepackage{amsmath, amssymb} % Para fórmulas matemáticas
\\usepackage{graphicx} % Para inserir gráficos/imagens
\\usepackage{hyperref} % Para hiperlinks no sumário
\\usepackage{listings} % Para inclusão de código-fonte
\\usepackage{algorithm} % Para algoritmos
\\usepackage{algpseudocode} % Para pseudocódigo
\\usepackage{enumitem} % Para listas com formatação personalizada
\\usepackage{xcolor}

% ---- STYLE ---- 
\\definecolor{codegreen}{rgb}{0,0.6,0}
\\definecolor{codegray}{rgb}{0.5,0.5,0.5}
\\definecolor{codepurple}{rgb}{0.58,0,0.82}
\\definecolor{backcolour}{rgb}{0.95,0.95,0.92}

\\lstdefinestyle{mystyle}{
    backgroundcolor=\\color{backcolour},
    commentstyle=\\color{codegreen},
    keywordstyle=\\color{magenta},
    numberstyle=\\tiny\\color{codegray},
    stringstyle=\\color{codepurple},
    basicstyle=\\footnotesize,
    breakatwhitespace=false,
    breaklines=true,
    captionpos=b,
    keepspaces=true,
    numbers=left,
    numbersep=5pt,
    showspaces=false,
    showstringspaces=false,
    showtabs=false,
    tabsize=2
}

\\lstset{style=mystyle}
% ---- STYLE ---- 

\\title{ICPC Material}
\\author{Sniper Monkeys}
\\date{\\today}

\\begin{document}

\\maketitle
\\tableofcontents % Gera o sumário automaticamente

\\newpage
'''

def generate_overleaf(directory, output_file):
    with open(output_file, 'w') as f:
        f.write(initalize_doc())
        
        for root, dirs, files in os.walk(directory):
            # Calculate the level relative to the base directory
            relative_path = root.replace(directory, '')
            level = relative_path.count(os.sep)
            
            # Skip the base directory itself
            if level == 0:
                continue
            
            # Adjust the level so the first subfolder starts at \section
            adjusted_level = level - 1
            
            indent = '    ' * adjusted_level
            section = '\\' + (adjusted_level * 'sub') + r'section' + '{' + os.path.basename(root) + '}'
            f.write(indent + section + '\n')
            
            adjusted_level += 1
            
            for file in files:
                file_path = os.path.join(root, file)
                subsection = '\\' + (adjusted_level * 'sub') + r'section' + '{' + clean_filename(file) + '}'
                f.write(indent + '    ' + subsection + '\n')
                f.write(indent + '    ' + r'\begin{lstlisting}[language=C++]' + '\n')
                
                with open(file_path, 'r') as code_file:
                    f.write(code_file.read() + '\n')
                
                f.write(indent + '    ' + r'\end{lstlisting}' + '\n')
                f.write(indent + '    ' + r'\newpage' + '\n')
            
            adjusted_level -= 1
        
        f.write(r'\end{document}' + '\n')

# Exemplo de uso:
generate_overleaf('./material', 'output.tex')
