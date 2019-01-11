/*
 * Python binding to liblangid
 * Based on a tutorial by Dan Foreman-Mackey
 * http://dan.iel.fm/posts/python-c-extensions/
 * and on the implementation of chromium-compact-language-detector by Mike McCandless
 * https://code.google.com/p/chromium-compact-language-detector
 *
 * Marco Lui <saffsd@gmail.com>, September 2014
 */
#include <Python.h>
#include "liblangid.h"

/* Docstrings */
static char module_docstring[] =
    "This module provides an off-the-shelf language identifier.";
static char identify_docstring[] =
    "Identify the language of a piece of text.";

/* Available functions */
static PyObject *langid_identify(PyObject *self, PyObject *args);

/* Module specification */
static PyMethodDef module_methods[] = {
    {"identify", langid_identify, METH_VARARGS, identify_docstring},
    {NULL, NULL, 0, NULL}
};


/* Global LanguageIdentifier instance */
LanguageIdentifier *identifier;

/* Initialize the module */
static struct PyModuleDef Langid =
{
    PyModuleDef_HEAD_INIT,
    "LangID",
    module_docstring,
    -1,
    module_methods
};

PyMODINIT_FUNC PyInit__langid(void)
{
    PyObject *m =  PyModule_Create(&Langid);
    if (m == NULL)
        return;
    identifier = get_default_identifier();
    return m;
};

static PyObject *langid_identify(PyObject *self, PyObject *args)
{
    char *bytes;
    const char *lang;
    int numBytes;
    PyObject *ret;

    if (!PyArg_ParseTuple(args, "s#", &bytes, &numBytes))
        return NULL;
    
    /* Run our identifier */
    lang = identify(identifier, bytes, numBytes);

    /* Build the output object */
    ret = Py_BuildValue("s", lang);
    return ret;
}

