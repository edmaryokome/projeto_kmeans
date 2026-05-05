Pseudocódigo do algoritmo k-means

Entrada 
	k : número de grupos 
	data : base de dados com n objetos e m atributos (n x m) 
	it_max : número máximo de iterações
	
Saída 
	G : vetor com o rótulo dos objetos (n x 1) 
	C : matriz contendo a posição dos centroides (k x m)

Passos
	// Escolha aleatoriamente k números variando entre 1 e n 
	idx = randi(k,n);

	// Pegue a posição inicial dos centroides da base de dados 
	C = data[idx][1:m];

	// Calcular o valor da função de custo Eq(4.23) 
	fc = Funcao_Custo(data,C);
	
	// Inicializar variáveis de controle it = 0; // número de iterações
	dif_fc = 1; // diferença da função de custo entre as iterações
	
	// Atualização dos centroides
	Enquanto (it < it_max) ou (dif_fc <> 0) Faça{
		// Calcular a distância entre os centroides e os objetos D(n x k) 
		D = dist(data,C);
	
	// Determinar o centroide mais próximo para cada objeto 
	Para i=1:n Faça {
		pos = 1;
		aux = D[i][1]; Para j=2:k Faça {
		Se (aux > D[i][j]) Então {
			pos = j; aux = D[i][j]
		} 
			} 
			G[i] = pos; 
	}
	
	// Atualizar a posição dos centroides
	Para i=1:k Faça {
	// Encontrar os objetos de cada grupo 
		idx = ø;
		Para j=1:n Faça
		Se (G[j] == i) 
			Então idx.Add( j );
			
		// Calcular o valor médio de cada atributo dos objetos no grupo 
		C[i][1:m] = Media(data[idx][1:m]);

	}
	
	// Calcular valor da função de custo do novo agrupamento 
	fc_nova = Funcao_Custo(data,C);
	
	// Atualizar variáveis de controle 
	dif_fc = fc – fc_nova;
	fc = fc_nova; // armazenar o valor da função para próxima iteração 
	it = it + 1;
	}

CASTRO, Daniel Gomes Ferrari Leandro Nunes de. 
Introdução à Mineração de Dados: Conceitos Básicos, Algoritmos e Aplicações. 
Rio de Janeiro: Saraiva Uni, 2016. E-book. p.137. ISBN 978-85-472-0100-5. 
Disponível em: https://app.minhabiblioteca.com.br/reader/books/978-85-472-0100-5/. Acesso em: 06 abr. 2026.



			






