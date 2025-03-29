import {
  createContext,
  useContext,
  useState,
  useEffect,
  ReactNode,
} from "react";

interface AuthContextType {
  userId: number | null;
  login: (userId: number) => void;
  logout: () => void;
}

export const getUserId = (): number | null => {
  const userInfo = localStorage.getItem("userInfo");
  return userInfo ? Number(userInfo) : null;
};

export const saveUserId = (userId: number) => {
  localStorage.setItem("userInfo", JSON.stringify(userId));
};

export const clearUserId = () => {
  localStorage.removeItem("userInfo");
};

const AuthContext = createContext<AuthContextType | undefined>(undefined);

function AuthProvider({ children }: { children: ReactNode }) {
  const [userId, setUserId] = useState<number | null>(getUserId());

  useEffect(() => {
    if (userId !== null) {
      saveUserId(userId);
    }
  }, [userId]);

  const login = (id: number) => {
    setUserId(id);
  };

  const logout = () => {
    clearUserId();
    setUserId(null);
  };

  return (
    <AuthContext.Provider value={{ userId, login, logout }}>
      {children}
    </AuthContext.Provider>
  );
}

const useAuth = () => {
  const context = useContext(AuthContext);
  if (!context) {
    throw new Error("useAuth must be used within an AuthProvider");
  }
  return context;
};

export { AuthProvider, useAuth };
