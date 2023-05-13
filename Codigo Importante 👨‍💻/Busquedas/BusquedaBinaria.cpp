int binaria(int vector[],unsigned dimension,int datoBuscado)
{
    int desde = 0, hasta = dimension - 1, medio;
    do
    {
        medio = (desde + hasta) / 2;
        if (datoBuscado < vector[medio])
            hasta = medio - 1;
        else
            desde = medio + 1;
    } while (desde <= hasta && vector[medio] != datoBuscado);

    if (vector[medio] == datoBuscado)
    {
        return medio;
    }
    else
    {
        return -1;
    }
}