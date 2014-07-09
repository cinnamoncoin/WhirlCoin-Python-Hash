#include <Python.h>

#include "whirlpool.h"

static PyObject *whirlpool_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    whirlpool_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    whirlpool_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef whirlpoolMethods[] = {
    { "getPoWHash", whirlpool_getpowhash, METH_VARARGS, "Returns the proof of work hash using whirlpool hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef whirlpoolModule = {
    PyModuleDef_HEAD_INIT,
    "whirlpool_hash",
    "...",
    -1,
    whirlpoolMethods
};

PyMODINIT_FUNC PyInit_whirlpool_hash(void) {
    return PyModule_Create(&whirlpoolModule);
}

#else

PyMODINIT_FUNC initwhirlpool_hash(void) {
    (void) Py_InitModule("whirlpool_hash", whirlpoolMethods);
}
#endif
