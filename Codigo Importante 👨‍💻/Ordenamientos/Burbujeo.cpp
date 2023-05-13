void burbujeo(int vector[],unsigned dimension)
{
    unsigned i = 1, j;
    int aux;
    bool cambio;

    do
    {
        cambio = false;

        for (j = 0; j < dimension - i; j++)
        {
            if (vector[j] > vector[j + 1])
            {
                aux = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = aux;
                cambio = true;
            }
        }

        i++;
    } while (i < dimension && cambio);
}