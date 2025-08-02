#pragma once

#include <vector>
#include <string>

#define UCLASS(...)
#define UPROPERTY(...)
#define GENERATED_BODY()
#define BlueprintReadOnly
#define VisibleAnywhere
#define Replicated
#define Category(...)
#define check(x)
#define TEXT(x) x

class UObject {};
class UClass {};
class UActorComponent : public UObject {};
class UAnimInstance : public UObject {};
class USkeletalMesh : public UObject {};

struct FVector {
    float X, Y, Z;
    FVector(float x=0, float y=0, float z=0) : X(x), Y(y), Z(z) {}
};

struct FRotator {
    float Pitch, Yaw, Roll;
    FRotator(float p=0, float y=0, float r=0) : Pitch(p), Yaw(y), Roll(r) {}
};

class USkeletalMeshComponent : public UActorComponent {
public:
    void SetSkeletalMesh(USkeletalMesh*) {}
    void SetRelativeLocation(const FVector&) {}
    void SetRelativeRotation(const FRotator&) {}
    void SetAnimInstanceClass(UClass*) {}
};

class USpringArmComponent : public UActorComponent {
public:
    void SetupAttachment(UActorComponent*) {}
    float TargetArmLength = 0.0f;
    bool bUsePawnControlRotation = false;
    static constexpr const char* SocketName = "";
};

class UCameraComponent : public UActorComponent {
public:
    void SetupAttachment(USpringArmComponent*, const char* = "") {}
    bool bUsePawnControlRotation = false;
};

struct FRotationMatrix {
    explicit FRotationMatrix(const FRotator&) {}
    FVector GetUnitAxis(int) const { return FVector(); }
};

namespace EAxis { enum Type { X, Y, Z }; }

class AController {
public:
    FRotator GetControlRotation() const { return FRotator(); }
};

struct FActorTick { bool bCanEverTick = false; };

class AActor : public UObject {
public:
    UActorComponent* RootComponent = nullptr;
    FActorTick PrimaryActorTick;
};

class UInputComponent;

class ACharacter : public AActor {
public:
    AController* Controller = nullptr;
    bool bReplicates = false;
    USkeletalMeshComponent* GetMesh() { return &Mesh; }
    void AddMovementInput(const FVector&, float) {}
    void AddControllerYawInput(float) {}
    void AddControllerPitchInput(float) {}
    virtual void Jump() {}
    virtual void StopJumping() {}
    virtual void SetupPlayerInputComponent(UInputComponent*) {}
    virtual void GetLifetimeReplicatedProps(std::vector<int>&) const {}

private:
    USkeletalMeshComponent Mesh;
};

class UInputComponent : public UActorComponent {
public:
    template <typename UserClass, typename Func>
    void BindAxis(const char*, UserClass*, Func) {}
    template <typename UserClass, typename Func>
    void BindAction(const char*, int, UserClass*, Func) {}
};

enum EInputEvent { IE_Pressed, IE_Released };

template <typename T>
using TArray = std::vector<T>;
using FLifetimeProperty = int;

#define DOREPLIFETIME(Class, Property)

class AGameModeBase : public AActor {
public:
    UClass* DefaultPawnClass = nullptr;
};

namespace ConstructorHelpers {
    template <typename T>
    class FObjectFinder {
    public:
        T* Object = nullptr;
        explicit FObjectFinder(const char*) {}
        bool Succeeded() const { return false; }
    };

    template <typename T>
    class FClassFinder {
    public:
        UClass* Class = nullptr;
        explicit FClassFinder(const char*) {}
        bool Succeeded() const { return false; }
    };
}

template <typename T>
T* CreateDefaultSubobject(const char*) { return new T(); }
