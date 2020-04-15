# GTEXE
Sujet de l'exercice :

L'objectif est de réaliser une classe qui implémente une approximation de fonction générique. Le but est de le faire sans autres dépendances que la lib de maths de base.

Dans un premier temps, une fonction va être définie par un ensemble de paires (x_i,y_i), x_i et y_i réels. L'évalution de la fonction en une valeur x sera obtenue par interpolation linéaire entre les deux valeurs les plus proches. J'aimerais une complexité au plus logarithmique pour cette implémentation.
Je te demande donc d'abord de définir une classe fonction avec variables membres et les constructeurs adéquats. Il faudra en particulier une fonction pour définir la valeur en un point (F(x) = y) et une autre pour calculer la valeur interpolée en un point.

Ensuite, il faudrait ajouter des opérateurs surchargés pour la structure algébrique (+,-), multiplication par un scalaire et un operateur () pour faire de la classe un Functor.

Je propose ensuite d'ajouter une fonction pour extraire les zeros de la fonction et une autre pour appliquer une fonction mathématique. Par exemple (en C++):

Function Function::map(double (*f)(double)) const;

Dans certain cas, on voudrait faire une fonction dont la sortie (valeur y) est un angle. Cela complexifie l'interpolation parce que la différence entre 2 valeurs doit toujours être modulo 2 pi: si f(x1) = 179 deg et f(x2) = -179 deg, on veut f((x1+x2)/2) = 180. Je te demande donc de faire une classe héritée (disons AngularFunction) qui ne remplacera que la fonction d'évaluation.

Finalement, dans certain cas, on peut avoir une fonction définit en des millions de points. Je voudrais une proposition pour paralleliser l'implémentation de la fonction map définie ci-dessus. En python, cela ne marchera pas vraiment a cause du GIL, mais cela n'empêche pas de l'écrire en ignorant le GIL.

Pour cette dernière partie, tu seras obligée de dépendre de modules externes (pthread.h ou boost en C++ si tu n'utilises pas les std::thread de C++11), threading ou multiprocessing en python.

Solution :

N'ayant pas le droit aux vectors, j'ai crée une classe "Vector" avec les constructeurs, les attributs et les opérateurs surchargés en cohérence avec la problématique.

Un template classe "Vec" a été ainsi écrite notamment pour la partie multithreading.

Le fichier fcn.cpp contient une classe "Function" qui répond aux differentes questions de l'exercice (Interpolation, find_zeros une fonction d'éstimation de l'integral de la fonction selon la méthode des trapèzes).

La classe "AngularFunction" hérite cette classe, mais qui remplace la fonction de l'interpolation. La fonction "fcnModifier" a été écrite avec un pointeur sur une autre fonction.

2 méthodes de parallelismes ont été propsées pour la boucle "for" de cette dernière. Une avec des threads et une autre avec std::async . La première fonctionne correctement mais dépend de la library vector. La méthode async n'est pour l'instant pas fonctionnel avec ma template class "Vec". Je suis toujours en train de chercher une solution notamment pour les méthode "emplace_back" ,"begin" et "end" de la calsse "Vec" afin de faire fonctionner le multithreading.
