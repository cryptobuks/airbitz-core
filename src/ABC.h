/**
 * @file
 * AirBitz Core API function prototypes
 *
 *
 * @author Adam Harris
 * @version 1.0
 */

#ifndef ABC_h
#define ABC_h

#include <stdbool.h>

/** The maximum buffer length for default strings in the system */
#define ABC_MAX_STRING_LENGTH 256

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     * AirBitz Core Condition Codes
     *
     * All AirBitz Core functions return this code.
     * ABC_CC_OK indicates that there was no issue.
     * All other values indication some issue.
     *
     */
    typedef enum eABC_CC
    {
        /** The function completed without an error */
        ABC_CC_Ok = 0,
        /** An error occured */
        ABC_CC_Error = 1,
        /** Unexpected NULL pointer */
        ABC_CC_NULLPtr = 2,
        /** Max number of accounts have been created */
        ABC_CC_NoAvailAccountSpace = 3,
        /** Could not read directory */
        ABC_CC_DirReadError = 4,
        /** Could not open file */
        ABC_CC_FileOpenError = 5,
        /** Could not read from file */
        ABC_CC_FileReadError = 6,
        /** Could not write to file */
        ABC_CC_FileWriteError = 7,
        /** No such file */
        ABC_CC_FileDoesNotExist = 8,
        /** Unknown crypto type */
        ABC_CC_UnknownCryptoType = 9,
        /** Invalid crypto type */
        ABC_CC_InvalidCryptoType = 10,
        /** Decryption error */
        ABC_CC_DecryptError = 11,
        /** Decryption failed checksum */
        ABC_CC_DecryptBadChecksum = 12,
        /** Encryption error */
        ABC_CC_EncryptError = 13,
        /** Scrypt error */
        ABC_CC_ScryptError = 14,
        /** Account already exists */
        ABC_CC_AccountAlreadyExists = 15,
        /** Account does not exist */
        ABC_CC_AccountDoesNotExist = 16,
        /** JSON parsing error */
        ABC_CC_JSONError = 17,
        /** Incorrect password */
        ABC_CC_BadPassword = 18,
        /** Wallet already exists */
        ABC_CC_WalletAlreadyExists = 19
    } tABC_CC;

    /**
     * AirBitz Request Types
     *
     * The requests results structure contains this
     * identifier to indicate which request it is 
     * associated with.
     *
     */
    typedef enum eABC_RequestType
    {
        /** Account sign-in request */
        ABC_RequestType_AccountSignIn = 0,
        /** Create account request */
        ABC_RequestType_CreateAccount = 1,
        /** Set account recovery questions */
        ABC_RequestType_SetAccountRecoveryQuestions = 2,
        /** Create wallet request */
        ABC_RequestType_CreateWallet = 3
    } tABC_RequestType;
    
    /**
     * AirBitz Core Error Structure
     *
     * This structure contains the detailed information associated
     * with an error.
     * All AirBitz Core functions should offer the
     *
     */
    typedef struct sABC_Error
    {
        /** The condition code code */
        tABC_CC code;
        /** String containing a description of the error */
        char szDescription[ABC_MAX_STRING_LENGTH + 1];
        /** String containing the function in which the error occurred */
        char szSourceFunc[ABC_MAX_STRING_LENGTH + 1];
        /** String containing the source file in which the error occurred */
        char szSourceFile[ABC_MAX_STRING_LENGTH + 1];
        /** Line number in the source file in which the error occurred */
        int  nSourceLine;
    } tABC_Error;
    
    /**
     * AirBitz Core Asynchronous Structure
     *
     * This structure contains the detailed information associated
     * with an asynchronous BitCoin event.
     *
     */
    typedef struct sABC_AsyncBitCoinInfo
    {
        /** data pointer given by caller at init */
        void    *pData;
        
        /** String containing a description of the event */
        char    szDescription[ABC_MAX_STRING_LENGTH + 1];
    } tABC_AsyncBitCoinInfo;
    
    /**
     * AirBitz Core Request Results Structure
     *
     * This structure contains the detailed information associated
     * with a create account result.
     *
     */
    typedef struct sABC_RequestResults
    {
        /** request type these results are associated with */
        tABC_RequestType    requestType;

        /** data pointer given by caller at initial create call time */
        void                *pData;
        
        /** true if successful */
        bool                bSuccess;
        
        /** information the error if there was a failure */
        tABC_Error          errorInfo;
    } tABC_RequestResults;
    
    /**
     * AirBitz Currency Structure
     *
     * This structure contains the id's and names of all the currencies.
     *
     */
    typedef struct sABC_Currency
    {
        /** currency ISO 4217 code */
        char    *szCode;
        
        /** currency ISO 4217 num */
        int     num;
        
        /** currency description */
        char    *szDescription;

        /** currency countries */
        char    *szCountries;
    } tABC_Currency;
    
    /**
     * AirBitz Asynchronous BitCoin event callback
     *
     * This is the form of the callback that will be called when there is an
     * asynchronous BitCoin event.
     *
     */
    typedef void (*tABC_BitCoin_Event_Callback)(const tABC_AsyncBitCoinInfo *pInfo);
    
    /**
     * AirBitz Request callback
     *
     * This is the form of the callback that will be called when a request
     * call has completed.
     *
     */
    typedef void (*tABC_Request_Callback)(const tABC_RequestResults *pResults);
    
    
    tABC_CC ABC_Initialize(const char                   *szRootDir,
                           tABC_BitCoin_Event_Callback  fAsyncBitCoinEventCallback,
                           void                         *pData,
                           const unsigned char          *pSeedData,
                           unsigned int                 seedLength,
                           tABC_Error                   *pError);
    
    tABC_CC ABC_ClearKeyCache(tABC_Error *pError);
    
    tABC_CC ABC_SignIn(const char *szUserName,
                       const char *szPassword,
                       tABC_Request_Callback fRequestCallback,
                       void *pData,
                       tABC_Error *pError);
    
    tABC_CC ABC_CreateAccount(const char *szUserName,
                              const char *szPassword,
                              const char *szPIN,
                              tABC_Request_Callback fRequestCallback,
                              void *pData,
                              tABC_Error *pError);
    
    tABC_CC ABC_SetAccountRecoveryQuestions(const char *szUserName,
                                            const char *szPassword,
                                            const char *szRecoveryQuestions,
                                            const char *szRecoveryAnswers,
                                            tABC_Request_Callback fRequestCallback,
                                            void *pData,
                                            tABC_Error *pError);
    
    tABC_CC ABC_CreateWallet(const char *szUserName,
                             const char *szPassword,
                             const char *szWalletName,
                             int        currencyNum,
                             unsigned int attributes,
                             tABC_Request_Callback fRequestCallback,
                             void *pData,
                             tABC_Error *pError);
    
    tABC_CC ABC_GetCurrencies(tABC_Currency **paCurrencyArray,
                              int *pCount,
                             tABC_Error *pError);
    
    tABC_CC ABC_GetPIN(const char *szUserName,
                       const char *szPassword,
                       char **pszPIN,
                       tABC_Error *pError);
    
    tABC_CC ABC_SetPIN(const char *szUserName,
                       const char *szPassword,
                       const char *szPIN,
                       tABC_Error *pError);
    
    tABC_CC ABC_GetCategories(const char *szUserName,
                              char ***paszCategories,
                              unsigned int *pCount,
                              tABC_Error *pError);
    
    tABC_CC ABC_AddCategory(const char *szUserName,
                            char *szCategory,
                            tABC_Error *pError);
    
    tABC_CC ABC_RemoveCategory(const char *szUserName,
                               char *szCategory,
                               tABC_Error *pError);
    
    tABC_CC ABC_RenameWallet(const char *szUserName,
                             const char *szPassword,
                             const char *szUUID,
                             const char *szNewWalletName,
                             tABC_Error *pError);
    
    // temp functions
    void tempEventA();
    void tempEventB();
    
#ifdef __cplusplus
}
#endif

#endif
