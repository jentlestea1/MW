  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// DC_SampleR2Database.h
//
// This file was automatically generated by an XSL program
//

#ifndef DC_SampleR2Database_H
#define DC_SampleR2Database_H

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/ParameterDatabase.h"
#include "DC_SampleR2Database_inc.h"
#include "../Qom/object.h"


/**
 * A sample database with intermediate level of robustness against illegal accesses 
 * to database parameters. This database contains real-typed gains. 
 * <p>
 * The code for this class was automatically generated by an XSL program
 * using as input the XML-based <i>application model</i>. 
 * This class offers a pointer-oriented and robust
 * implementation of the <code>ParameterDatabase</code> interface.
 * The price paid for the safety offered by this implementation
 * is a certain inefficiency both in terms of memory overhead and
 * run-time when accessing a parameter.
 * <p>
 * An indexed database maintains internal data structures that,
 * for each parameter in the database, store the following information:<ul>
 * <li>The pointer to the operational version of the parameter</li>
 * <li>The syntactical type of the parameter</li>
 * </ul>
 * These internal data structures are set up and initialized by the indexed
 * database component during its configuration procedure.
 * The parameter type information allows the component to perform run-time cheks 
 * on the access to the parameter values. Checks are performed on the 
 * legality of the parameter identifier and on the use of the 
 * correct accessor method for a parameter (e.g. the value
 * of a parameter of type float should only be accessed with method 
 * <code>getParameterFloat</code>). 
 * <p>
 * The memory overhead caused by this class is minimized when the 
 * parameter identifiers begin with a zero and when there are no "gaps"
 * in the parameter identifier. 
 * <p>
 * The default and operational tables are <i>not</i> defined by this class.
 * This class loads the tables using methods <code>setDefaultTable</code>
 * and <code>setOperationalTable</code>.
 * <p>
 * The configuration procedure for an instance of this class is as follows: <ul>
 * <li>Load the default table (method <code>setDefaultTable</code>)  </li>
 * <li>Load the operational table (method <code>setOperationalTable</code>)  </li>
 * <li>Reset the component instance (method <code>reset</code>)  </li>
 * </ul>
 * Note that an include file (<code>DC_SampleR2Database_inc.h</code>) 
 * is also automatically generated that defines symbolic names to access the parameters in the database. 
 * <p>
 * The getter and setter methods are implemented to be fast and efficient but this
 * makes them vulnerable to alignement problems on some processors. For instance,
 * the setter methods for integer-valued parameters is implemened as follows: <pre>
 *    void DC_BasicDatabase::setParameter(TD_DatabaseId parId, int newValue) {
 *         *( (int*)(pPar[parId]) ) = newValue;
 *    }</pre>
 * On some processors, the assignment will fail if location <code>pPar[parId]</code> does not
 * correspond to a longword (4 bytes) boundary. There is no check to ensure that this
 * is the case and it is the responsibility of the user to ensure that the database map
 * is such as to avoid this type of problems. The database map is defined in the 
 * XML document that is processed by the generator meta-component that generates the
 * database implementation. A more robust (but possibly slower) implementation
 * might use the <code>memcpy</code> library function to transfer the values of the
 * data between the database locations and the method variables.
 * @author Automatically Generated 
 * @version 1.0
 */
 
#define TYPE_DC_SAMPLER2DATABASE "dc_sampler2database"
void DC_SampleR2Database_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct  DC_SampleR2Database {
    ParameterDatabase parent;

    char *pDefaultTable;          // array of chars
    char *pOperationalTable;      // array of chars
    bool resetWasCalled;
    TD_DatabaseId tableLength;    // table length in bytes
    char **pPar;                  // pPar[i] holds the pointer to the i-th par 
    TD_DatabaseId maxParId;        // maximum value of parameter identifier
    // parType[i] holds a code representing the type of the i-th par: 
    char *parType;                 
};


struct DC_SampleR2DatabaseClass {
    ParameterDatabaseClass parent_class;
 
    /**
     * Copy the default table array onto the operational table array
     * and set up the internal
     * data structures that describe the position of the parameters in the
     * database and their type. 
     * An indexed database component maintains two internal data structures
     * that describe how the database is organized: <ul>
     * <li><i>The parameter pointer 
     * table <code>pPar</code></i>: 
     * <code>pPar[i]</code>
     * holds the pointer to the database parameter with parameter
     * identifier i. The operational version of the database is used. </li>
     * <li><i>The parameter type 
     * table <code>parType</code></i>: 
     * <code>parType[i]</code>
     * holds an integer that encodes the type of the database parameter with parameter
     * identifier i. </li>
     * </ul>
     * The initialization of these two tables is hardcoded in this method.
     * The information for generating the code comes from the XML file which 
     * describes the parameter database and which is used as input for generating
     * the code for this class.
     */
     void (*reset)(void *obj);


    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type int.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type int). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterInt)(void *obj, TD_DatabaseId parId, int newValue);

    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type unsigned int.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned int). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterUnsignedInt)(void *obj, TD_DatabaseId parId, unsigned int newValue);

    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type short.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type short). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterShort)(void *obj, TD_DatabaseId parId, short newValue);

    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type unsigned short.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned short). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterUnsignedShort)(void *obj, TD_DatabaseId parId, unsigned short newValue);

    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type char.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type char). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterChar)(void *obj, TD_DatabaseId parId, char newValue);

    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type unsigned char.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned char). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterUnsignedChar)(void *obj, TD_DatabaseId parId, unsigned char newValue);

    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type bool.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type bool). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterBool)(void *obj, TD_DatabaseId parId, bool newValue);

    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type float.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type float). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterFloat)(void *obj, TD_DatabaseId parId, float newValue);

    /**
     * Set the current value of a parameter interpreted as a parameter of
     * type double.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type double). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The database parameter is not
     * updated if the check fails.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
     void (*setParameterDouble)(void *obj, TD_DatabaseId parId, double newValue);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type int.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type int). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    int (*getParameterInt)(void *obj, TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type unsigned int.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned int). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    unsigned int (*getParameterUnsignedInt)(void *obj, TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type short.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type short). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    short (*getParameterShort)(void *obj, TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type unsigned short.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned short). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    unsigned short (*getParameterUnsignedShort)(void *obj, TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type char.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type char). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    char (*getParameterChar)(void *obj, TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type unsigned char.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned char). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    unsigned char (*getParameterUnsignedChar)(void *obj, TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type bool.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type bool). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    bool (*getParameterBool)(void *obj, TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type float.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type float). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    float (*getParameterFloat)(void *obj, TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a parameter of
     * type double.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type double). 
     * Failure of the checks results in
     * the generation of an assert error. If assertions are disabled, the checks
     * are ineffective. 
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    double (*getParameterDouble)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type int.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type int). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    int (*getParameterPointerInt)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type unsigned int.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned int). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    unsigned int (*getParameterPointerUnsignedInt)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type short.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type short). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    short (*getParameterPointerShort)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type unsigned short.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned short). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    unsigned short (*getParameterPointerUnsignedShort)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type char.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type char). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    char (*getParameterPointerChar)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type unsigned char.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type unsigned char). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    unsigned char (*getParameterPointerUnsignedChar)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type bool.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type bool). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    bool (*getParameterPointerBool)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type float.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type float). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    float (*getParameterPointerFloat)(void *obj, TD_DatabaseId parId);

    /**
     * Get the pointer to the operational table copy of the parameter 
     * interpreted as a parameter of type double.
     * Run-time checks are performed on the legality of the parameter identifier
     * and on the correctness of the parameter type (i.e. it is verified that
     * the parameter being accessed is internally recorded as a parameter of 
     * type double). 
     * Failure of the checks results in
     * the generation of an assert error and in the generation of an event report
     * for an event of type EVT_ILLEGAL_DB_ACCESS. The method returns a default value 
     * zero.
     * @param parId the identifier of the parameter to be set
     * @return the pointer to the parameter in the operational database
     */
    double (*getParameterPointerDouble)(void *obj, TD_DatabaseId parId);

     
     /**
     * Perform a class-specific configuration check on a basic database object:
     * verify that the default and operational tables have been loaded, that
     * method <code>reset</code> has been called, and that the table length
     * is greater than zero.
     * @see #reset
     * @return true if the database object is configured, false otherwise
     */
    bool (*isObjectConfigured)(void *obj);
};


#define DC_SAMPLER2DATABASE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_SampleR2DatabaseClass, obj, TYPE_DC_SAMPLER2DATABASE)

#define DC_SAMPLER2DATABASE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_SampleR2DatabaseClass, klass, TYPE_DC_SAMPLER2DATABASE)

#define DC_SAMPLER2DATABASE(obj) \
        OBJECT_CHECK(DC_SampleR2Database, obj, TYPE_DC_SAMPLER2DATABASE)


        DC_SampleR2Database* DC_SampleR2Database_new(void);
   

///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the default table. This method assumes that the default table has
 * been defined and initialized by the caller. The method does not perform
 * any action on the table. It simply loads its address and will use it
 * for accessing the table entries.
 * <p>
 * This is an initialization method.
 * @param pDefTable the starting address of the default table
 */
void DC_SampleR2Database_setDefaultTable(DC_SampleR2Database *this, char* pDefTable);

/**
 * Load the operational table. This method assumes that the operational table has
 * been defined and initialized by the caller. The method does not perform
 * any action on the table. It simply loads its address and will use it
 * for accessing the table entries.
 * <p>
 * This is an initialization method.
 * @param pOperTable the starting address of the operational table
 */
void DC_SampleR2Database_setOperationalTable(DC_SampleR2Database *this, char* pOperTable);

#endif  
