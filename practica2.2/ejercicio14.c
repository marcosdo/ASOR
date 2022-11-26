/*

[cursoredes@localhost P2]$ cat /proc/locks
1: POSIX  ADVISORY  WRITE 1578 fd:00:53013121 0 EOF
2: POSIX  ADVISORY  WRITE 1571 fd:00:53013120 0 EOF
3: POSIX  ADVISORY  WRITE 1564 fd:00:53012991 0 EOF
4: POSIX  ADVISORY  WRITE 1554 fd:00:53012987 0 EOF
5: POSIX  ADVISORY  WRITE 1351 00:13:21364 0 EOF
6: FLOCK  ADVISORY  WRITE 1314 fd:00:17458434 0 EOF
7: FLOCK  ADVISORY  WRITE 1314 fd:00:30831 0 EOF
8: FLOCK  ADVISORY  WRITE 1046 00:13:19967 0 EOF
9: POSIX  ADVISORY  WRITE 1045 00:13:19949 0 EOF
10: POSIX  ADVISORY  WRITE 784 00:13:16343 0 EOF
12: POSIX  ADVISORY  WRITE 480 00:13:12778 0 EOF


1.- El identificador del bloqueo.

2.- Tipo de bloqueo (POSIX si el bloqueo se hizo con fcntl y FLOCK si se creó con flock.)

3.- Modo de bloqueo (ADVISORY o MANDATORY)

-Advisory: El acceso a los datos está permitido y evita otros bloqueos.

-Mandatory: El acceso a los datos está denegado mientras esté bloqueado.

4.- Tipo de bloqueo (WRITE o READ), correspondiente a bloqueos compartidos o exclusivos.

-Write (Exclusivo): El proceso está escribiendo por lo que no se puede leer ni escribir en el área bloqueada.

-Read (Compartido): El proceso está leyendo por lo que el área no puede ser modificada.

5.- PID del proceso que tiene el bloqueo sobre el fichero.

6.- Tres números separados por :, que identifican el fichero bloqueado.

7.- Byte donde comienza el bloqueo en el fichero.

8.- Byte donde acaba el bloqueo del fichero.


*/